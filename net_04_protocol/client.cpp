/* A simple client */

#include "Client.h"

int connect_socket (int domain, int type, int protocol) {
    return socket( domain , type, protocol );
}

int main(int argc, char **argv) {
    
    bool valid = true ;

    if (valid && argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]); 
       valid = false ; 
    }
    
    if( valid ) {
        const char * hostName   = argv[1];
        const char * portNo     = argv[2];

        Client client;
        client.connectServer( hostName, portNo );
    }

    return 0;
}

 

// -- 