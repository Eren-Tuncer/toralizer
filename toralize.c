#include "toralize.h"


Req* request(const char* dstip,const int dstport){
    
    Req * req = malloc(reqsize);
    
    req->vn = 4;
    req->cd = 1;
    req->dstport = htons(dstport);
    req->dstip = inet_addr(dstip);
    strncpy(req->userid, USERNAME, 8);
    
    return req;
    
    }

int main(int argc, char *argv[]){

    char *hostname;
    int port, s;
    struct sockaddr_in sock;
    Req* req;
    Res* res;
    char buff[ressize];
    int success;

    if (argc<3){
        fprintf(stderr, "Usage: %s <host> <port>\n",
        argv[0]);
        return -1;
    }

    hostname = argv[1];
    port = atoi(argv[2]);

    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(s<0){
        perror("socket");
        return -1;
    }
    
    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if(connect(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1 ;
    }

    printf("Connected to proxy\n");
    
    req = request(hostname,port);
    
    write(s, req, reqsize);
    
    memset(buff, 0, ressize); // reset buffer
    
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
    //1.17 de kaldım // proxy çalışmadı
    printf("Successfully connected through the proxy to"
    "%s:%d", hostname, port);

    close(s);
    free(req);
    
    return 0;
}