#include "Client.h"

#include "zf_log.h"

Client::Client() {
};

int Client::connectServer(const char * hostName , const char * portNo ) {
    FILE * console = stdout ;

    struct hostent *server = gethostbyname( hostName );
    if (server == NULL) {
        ZF_LOGI( "ERROR no such host or port" );
    } else {
        int portno = atoi( portNo );
        int sockfd = connect_socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            ZF_LOGI( "ERROR opening socket" );
        } else {
            struct sockaddr_in serv_addr;
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
            serv_addr.sin_port = htons(portno);

            if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                ZF_LOGI( "ERROR connecting" );
            } else {
                Socket * socket = & this->socket ;
                socket->sockfd     = sockfd;
                socket->valid      = 1 ;
                socket->console    = console ;

                pthread_t readThread ;
                pthread_create (&readThread, NULL, readMessageThread, this );
            }
        }
    }

    return this->socket.valid ;
}

void * Client::readMessageThread( void * args ) {
    Client * client = (Client *) args ;
    client->readOpCode();
    return 0;
}

void Client::readOpCode( ) {
    Socket * socket = & this->socket ;

    ZF_LOGI( "Reading Thread started." );

    while( socket->valid  ) {
        OpCodeMsg message = socket->readOpCode();

        if ( not socket->valid ) {
            ZF_LOGI( "ERROR reading from socket" );
        } else if( socket->valid ) {
            this->processOpCode( & message );
        }
    }
}

//
