#include "Client.h"

#include "zf_log.h"

Client::Client() {
};

int Client::connectServer(const char * hostName , const char * portNo ) {
    struct hostent *server = gethostbyname( hostName );

    if ( NULL == server ) {
        ZF_LOGI( "ERROR no such host or port" );
    } else {
        int portno = atoi( portNo );
        int sockfd = connect_socket(AF_INET, SOCK_STREAM, 0);
        if ( 0 > sockfd ) {
            ZF_LOGI( "ERROR opening socket" );
        } else {
            struct sockaddr_in serv_addr;
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
            serv_addr.sin_port = htons(portno);

            if ( 0 > connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) ) {
                ZF_LOGI( "ERROR connecting" );
            } else {
                Socket * socket = & this->socket ;
                socket->sockfd     = sockfd;
                socket->valid      = 1 ;

                pthread_t readThread ;
                pthread_create (&readThread, NULL, runReadOpCodeThread, this );
            }
        }
    }

    return this->socket.valid ;
}

void * Client::runReadOpCodeThread( void * args ) {
    Client * client = (Client *) args ;

    return client->runReadOpCodeWhile();
}

void * Client::runReadOpCodeWhile( ) {
    Socket * socket = & this->socket ;

    ZF_LOGI( "Reading Thread started." );

    int idx = 0 ;

    while( socket->valid  ) {
        OpCode * opCode = socket->readOpCode();

        if ( false == socket->valid ) {
            ZF_LOGI( "ERROR reading from socket" );
        } else if( socket->valid and NULL != opCode ) {
            ZF_LOGI( "[%04d] Processing opCode ....", idx );
            this->processOpCode( opCode );
            ZF_LOGI( "[%04d] Done processing opCode.", idx );
            idx ++;
        } else if( NULL == opCode ) {
            ZF_LOGI( "OpCode is NULL." );
        }
    }

    return 0;
}

//
