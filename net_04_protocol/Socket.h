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
    FILE * console ;

    ChatRoom * chatRoom ;

    public: Socket() { 
        this->valid = true ; 
        this->console = stdout ; 
    }

    // read a client message
    public: Message readMessage( ) {
        char readMsg[1024 + 1]; 
        bzero( readMsg, sizeof( readMsg ));
        int sockfd = this->sockfd ; 
        int rn = 0 ; 
        char * buff = readMsg;
        do {
            buff += rn ;
            rn = read(sockfd, buff, 1);
        } while( this->valid && -1 < rn && '\n' != *buff );

        Message message ;
        message.clientId = this->clientId;
        
        if( 0 > rn ) {
            this->valid = false;
            message.valid = false ; 
            message.text = "";
        } else if( -1 < rn ) {
            message.valid = true ;
            message.text = readMsg ;
        }

        return message;
    }

    // write a message
    public: void writeMessage( Message * message ) {
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        message->text.c_str();
        const char * name = ( message->clientId == this->clientId ) ? "* " : "" ;  
        snprintf ( sendMsg, sizeof(sendMsg), "%s%s", name, message->text.c_str() ); 

        int wn = 0 ; 
        wn = this->writeMessageOnSocket( sockfd, sendMsg );      

        if (wn < 0) {
            this->valid = false ; 
        }
    }

    // write a message to the client
    private: int writeMessageOnSocket( int sockfd, char * sendMsg ) {
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
        
        return wn;
    }

} ;

// --