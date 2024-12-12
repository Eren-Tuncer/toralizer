/* toralize.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>

#define PROXY "192.111.130.2"
#define PROXYPORT   4145
#define USERNAME "toraliz"
#define reqsize sizeof(struct proxy_request)
#define ressize sizeof(struct proxy_response)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;


struct proxy_request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8];
};

struct proxy_response{
        
        int8 vn;
        int8 cd;
        int16 _;
        int32 __;
 
 } ;

 typedef struct proxy_request Req;
 typedef struct proxy_response Res;

Req* request(struct sockaddr_in*);  
int connect(int , const struct sockaddr*,socklen_t );