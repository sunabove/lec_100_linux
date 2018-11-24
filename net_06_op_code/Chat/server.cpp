/* A simple server */
#include <stdio.h>

#include "Server.h"

int main(int argc, char **argv) { 

    const char * portNo = argc < 2 ? "100" : argv[1];
    Server server ;
    server.runServer( portNo );
    
    return 0;
} 
//