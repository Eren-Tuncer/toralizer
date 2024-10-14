/*toralize.c*/

#include "toralize.h"


/*
./toralize <IP> <PORT> 
*/


int main(int argc, char *argv[]){

    char *hostname;
    int port;

    if (argc<3){
        fprintf(stderr, "Usage: %s <host> <port>\n",
        argv[0]);
        return(-1);
    }

    host = argv[1];
    port = atoi(argv[2]);
}