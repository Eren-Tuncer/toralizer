#include "toralize.h"


Req* request(struct sockaddr_in * sock2addr){
    
    Req * req = malloc(reqsize);
    
    req->vn = 4;
    req->cd = 1;
    req->dstport = sock2addr->sin_port;
    req->dstip = sock2addr->sin_addr.s_addr;
    strncpy(req->userid, USERNAME, 8);
    
    return req;
    
    }

int connect(int sock2, const struct sockaddr *sock2addr,
        socklen_t addrlen){
    

    int s;
    struct sockaddr_in sock;
    Req* req;
    Res* res;
    char buff[ressize];
    int success;
    char tmp[512];

    int (*cp)(int , const struct sockaddr *,
                   socklen_t );

    
    cp = dlsym(RTLD_NEXT,"connect");
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(s<0){
        perror("socket");
        return -1;
    }
    
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if(cp(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1;
    }

    printf("Connected to proxy\n");
    
    req = request((struct sockaddr_in *)sock2addr);
    
    write(s, req, reqsize); 
    
    memset(buff, 0, ressize); // memset used to reset response buffer
    
    if(read(s, buff, ressize)<1){
        
        perror("read");
        free(req);
        close(s);

        return -1;
    }
    
    res = (Res*)buff;
    
    success = (res->cd == 90);
    
    if(!success){
        fprintf(stderr, "Unable to traverse " 
        "the proxy, error code: %d\n",
        res->cd);
        
        close(s);
        free(req);

        return -1;
    }
    
    printf("Successfully connected through the proxy to "
    "%s:%d\n", hostname, port);
    memset(tmp, 0, 512);
    snprintf(tmp, 512
    ,"HEAD / HTTP/1.0\r\n"
    "Host: www.networktechnology.org\r\n"
    "\r\n");

    write(s, tmp, strlen(tmp));

    memset(tmp, 0, 512);
    read(s, tmp,511);
    printf("'%s'\n",tmp);

    close(s);
    free(req);
    
    return 0;
}