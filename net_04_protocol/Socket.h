#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <vector>
#include <string>

#include "Message.h" 

class ChatRoom ;

class Socket  {
    public: 

    bool valid ; 
    int sockfd;
    int clientId ;
    const char * appName ;  
    ChatRoom * chatRoom ; 
    FILE * console ;

    public:

    Socket() { 
        this->valid = 1; 
        this->console = stdout ; 
    }

    // read a client message
    int readClientMessage( char * readMsg ) {
        int sockfd = this->sockfd ; 
        int rn = 0 ; 
        char * buff = readMsg;
        do {
            buff += rn ;
            rn = read(sockfd, buff, 1);
        } while( -1 < rn && '\n' != *buff );

        return rn ;
    } 

    // write a message
    void writeMessage( Message * message ) {
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        message->text.c_str();
        const char * name = ( message->clientId == this->clientId ) ? "* " : "" ;  
        snprintf ( sendMsg, sizeof(sendMsg), "%s%s", name, message->text.c_str() ); 

        int wn = 0 ; 
        wn = this->writeClientMessage( sockfd, sendMsg );                
        if (wn < 0) {
            this->valid = false ; 
        }
    }

    // write a message to the client
    int writeClientMessage( int sockfd, char * sendMsg ) {
        const int msgLen = strlen( sendMsg );
        int wn = 0 , twn = 0 ;
        char * buff = sendMsg ;
        do {  
            twn  += wn; 
            buff += wn ; 
            wn = write( sockfd, buff, msgLen - twn );        
        } while ( -1 < wn && twn < msgLen );

        if ( 0 < msgLen && '\n' != sendMsg[ msgLen -1 ] ) { 
            wn += write( sockfd , "\n", 1 );
        }

        fprintf(console, "\nMsg sent to client(%03d): %s" , clientId, sendMsg );
        fflush( console );

        return wn;
    }

} ;

// --