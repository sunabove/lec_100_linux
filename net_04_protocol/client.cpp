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
        
        const char * str = message->text.c_str();
        
        fprintf( console, "%s", str );

        if( '\n' != str[ strlen(str) - 1 ] ) {
            fprintf( console, "\n" );
        }
        fflush( console );

        return 1; 
    }
};

int main(int argc, char **argv) {
    FILE * console = stdout ;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    ClientImpl client ;
    const char * hostName = argv[1];
    const char * portNo = argv[2];
    client.connectServer( hostName, portNo );

    pthread_t readThread ;    
    pthread_create (&readThread, NULL, ClientImpl::readMessageThread, & client ); 

    client.writeMessageThread( ); 

    /*  Wait for the threads to exit. */
    
    fprintf( console, "\nGood bye!\n" );

    return 0;
} 

// -- 