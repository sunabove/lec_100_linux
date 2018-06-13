/* client */ 

#include "Client.h"

int connect_socket (int domain, int type, int protocol) {
    return socket ( domain, type, protocol) ;
}

class ClientImpl : public Client {

    public: ClientImpl() {

    }

    public: int processMessage( Message * message ) {
        FILE * console = stdout ; 
        fprintf( console, "%s", message->text.c_str() );
        fflush( console );

        return 1; 
    }
};

int main(int argc, char **argv) {
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    ClientImpl client ;
    const char * hostName = argv[1];
    const char * portNo = argv[2];
    client.connectServer( hostName, portNo );

    return 0;
} 

// -- 