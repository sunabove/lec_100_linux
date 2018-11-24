/* A simple server */
#include <stdio.h>

#include "Server.h"

int main(int argc, char **argv) { 

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    } else {
        const char * portNo = argv[1];
        Server server ;
        server.runServer( portNo );
    }
    
    return 0;
} 
//