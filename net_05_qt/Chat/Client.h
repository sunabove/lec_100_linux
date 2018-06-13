#pragma once

/* A simple client */
#include <stdio.h>

#include "Socket.h"

int connect_socket (int domain, int type, int protocol) ;

class Client { 
    public : 
        Socket socket ;
        bool connected ;

    public : Client() {
        this->connected = false ;
    };

    public: virtual int processMessage( Message * message ) = 0 ;

    public: int connectServer(const char * hostName , const char * portNo ) {
        FILE * console = stdout ; 
        
        struct hostent *server = gethostbyname( hostName );
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        
        int portno = atoi( portNo ); 
        int sockfd = connect_socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket"); 
            exit( 1 );
        }

        struct sockaddr_in serv_addr;
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            this->connected = false ;
            perror("ERROR connecting");
        } else {
            Socket * socket = & this->socket ;
            socket->sockfd     = sockfd;
            socket->valid      = 1 ;
            socket->console    = console ;

            this->connected = true ;

            pthread_t readThread ;
            pthread_create (&readThread, NULL, readMessageThread, this );
        }

        return this->connected ;
    }

    public: static void * readMessageThread( void * args ) {
        Client * client = (Client *) args ; 
        client->readMessage();    
        return 0;    
    }

    public: void readMessage( ) { 
        Socket * socket = & this->socket ; 
        FILE * console  = socket->console  ; 
        
        fprintf( console, "\n%s\n", "Reading Thread started." );
        fflush( console );

        size_t readMsgCount = 0 ; 
        while( socket->valid  ) { 
            bool doLog = false ; 
            if( doLog ){
                fprintf( console, "\n[%03zu] Reading a line ..." , readMsgCount );
                fflush( console );
            }

            Message message = socket->readMessage();

            if( doLog ) {
                fprintf( console, " done\n" );
                fflush( console );
            }

            if ( false == socket->valid ) {
                socket->valid = false ; 
                perror("ERROR reading from socket");
            } else if( socket->valid ) {
                readMsgCount ++;
                this->processMessage( & message );
                //fprintf( console, "%s", message.text.c_str() );
                //fflush( console ); 
            }
        }
    }
    
};

// -- 
