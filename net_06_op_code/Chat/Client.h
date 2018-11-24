#pragma once

/* A simple client */
#include <stdio.h>

#include "Socket.h"
#include "zf_log.h"

int connect_socket (int domain, int type, int protocol) ;

class Client { 
    public : 
        Socket socket ;

    public : Client() {

    };

    public: virtual int processOpCode( OpCode * message ) = 0 ;

    public: int connectServer(const char * hostName , const char * portNo ) {
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

    public: static void * readMessageThread( void * args ) {
        Client * client = (Client *) args ; 
        client->readMessage();    
        return 0;    
    }

    public: void readMessage( ) { 
        Socket * socket = & this->socket ;
        
        ZF_LOGI( "Reading Thread started." );

        size_t readMsgCount = 0 ; 
        bool doLog = true ;

        while( socket->valid  ) { 

            if( doLog ){
                ZF_LOGI( "[%03zu] Reading a line ..." , readMsgCount );
            }

            OpCodeMsg message = socket->readOpCode();

            if( doLog ) {
                ZF_LOGI( " done." );
            }

            if ( false == socket->valid ) {
                socket->valid = false ; 
                ZF_LOGI( "ERROR reading from socket" );
            } else if( socket->valid ) {
                readMsgCount ++;
                this->processOpCode( & message );
                //fprintf( console, "%s", message.text.c_str() );
                //fflush( console ); 
            }
        }
    }
    
};

//
