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
    FILE * stream ;
    unsigned int clientId ;
    const char * appName ;  
    ChatRoom * chatRoom ; 
    FILE * console ;
    unsigned int readMessageCount ;

    // constructor
    public: Socket(const int sockfd) { 
        this->stream = fdopen( sockfd, "r+" );
        this->valid = true ; 
        this->console = stdout ; 
        this->readMessageCount = 0 ; 
    }
    // -- constructor

    // read a client message
    public: Message readMessage( ) {
        char readMsg[2048];
        bzero(readMsg, sizeof(readMsg));

        FILE * stream = this->stream ; 
        char * buff = readMsg;
        int c ;
        do {
            c = fgetc( stream );
            if( EOF == c ) {
                // error
            } else {  
                *buff = (char) c;
                buff ++ ;
            } 
        } while( EOF != c && '\n' != *buff );

        Message message ;
        message.clientId = this->clientId ; 
        message.text  = EOF == c ? "" : readMsg ;
        message.valid = EOF == c ? false : true ; 

        this->readMessageCount += message.valid ? 1 : 0 ; 
        
        return message ;
    } 

    public : int writeMessage( const char * text ) {
        Message message ;
        message.clientId = this->clientId ;
        message.text = text ;

        return this->writeMessage( & message );
    }

    // write a message
    public: int writeMessage( Message * message ) {
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        message->text.c_str();
        const char * name = ( message->clientId == this->clientId ) ? "* " : "" ;  
        snprintf ( sendMsg, sizeof(sendMsg), "%s%s", name, message->text.c_str() ); 

        int wn = 0 ; 
        wn = this->writeMessageOnStream( sendMsg );                
        
        this->valid = -1 < wn ; 

        return wn;
    }

    // write a message to the client
    private: int writeMessageOnStream( char * sendMsg ) {
        FILE * stream = this->stream ; 
        const int msgLen = strlen( sendMsg );
        char * buff = sendMsg ;
        int c ;
        int wn = 0 ; 
        do {  
            c = fputc( *buff , stream );
            wn = ( EOF == c ) ? 0 : 1 ;
        } while ( EOF != c && msgLen > wn );

        if ( EOF != c && 0 < msgLen && '\n' != sendMsg[ msgLen -1 ] ) { 
            c = fputc( '\n' , stream );
        }

        if( EOF == c ) {
            this->valid = false ;
        } else if( EOF != c ) {
            fflush( stream );
        }

        fprintf(console, "\nMsg sent to client(%03d): %s" , clientId, sendMsg );
        fflush( console );

        return wn;
    }

    public: void close() {
        FILE * stream = this->stream ;
        if( NULL != stream ) {
            fflush( stream );
            fclose( stream );
            this->stream = NULL ;
        }
    }

} ;

// --