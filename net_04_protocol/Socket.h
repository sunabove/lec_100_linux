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
    unsigned int clientId ;
    const char * appName ;  
    ChatRoom * chatRoom ; 
    FILE * console ;
    unsigned int readMessageCount ;

    public:

    Socket() { 
        this->valid = true ; 
        this->console = stdout ; 
        this->readMessageCount = 0 ; 
    }

    // read a client message
    Message readMessage( ) {
        char readMsg[2048];
        bzero(readMsg, sizeof(readMsg));

        int sockfd = this->sockfd ; 
        int rn = 0 ; 
        char * buff = readMsg;
        do {
            buff += rn ;
            rn = read(sockfd, buff, 1);
        } while( -1 < rn && '\n' != *buff );

        Message message ;
        message.clientId = this->clientId ; 
        message.text = -1 < rn ? readMsg : "" ;
        message.valid = -1 < rn ? true : false ; 

        this->readMessageCount += message.valid ? 1 : 0 ; 
        
        return message ;
    } 

    public :
    int writeMessage( const char * text ) {
        Message message ;
        message.clientId = this->clientId ;
        message.text = text ;

        return this->writeMessage( & message );
    }

    // write a message
    int writeMessage( Message * message ) {
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        message->text.c_str();
        const char * name = ( message->clientId == this->clientId ) ? "* " : "" ;  
        snprintf ( sendMsg, sizeof(sendMsg), "%s%s", name, message->text.c_str() ); 

        int wn = 0 ; 
        wn = this->writeClientMessage( sockfd, sendMsg );                
        
        this->valid = -1 < wn ; 

        return wn;
    }

    // write a message to the client
    private: int writeClientMessage( int sockfd, char * sendMsg ) {
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