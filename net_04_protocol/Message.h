#pragma once

#include <string.h> 
#include <unistd.h>

#include <string>

class Message {
    public:
        unsigned int    clientId ;
        unsigned int    textSize ;
        std::string     text ;

    public: Message() {
        this->text = "" ;
        this->textSize = 0 ; 
        this->clientId = 0 ; 
    } 
    
    public: Message(const Message & message) {
        this->clientId  = message.clientId;
        this->textSize  = message.textSize ;
        this->text      = message.text ; 
    }

    // read a client message
    public: int readMessage( int sockfd ) {
        int valid = 1;
        valid = valid && this->readHead( sockfd );
        valid = valid && this->readBody( sockfd );

        return valid ; 
    }

    private: int readDataOnSocket( int sockfd, void * data , const int size ) {
        int trn = 0 ;
        int rn = 0 ;
        char * buff = (char *) data ;
        do {  
            rn = read( sockfd, buff, size - trn );
            buff += rn ; 
            trn  += rn; 
        } while ( -1 < rn && trn < size );

        return rn ; 
    }

    private: int readHead( int sockfd ) {
        int valid = 1; 
        valid = this->readDataOnSocket( sockfd, & this->textSize , sizeof( this->textSize ) );

        return valid ; 
    }

    public: int readBody( int sockfd ) {
        int valid = 1; 

        int textSize = this->textSize ;

        char readMsg[textSize + 1]; 
        bzero( readMsg, sizeof( readMsg )); 
        
        valid = this->readDataOnSocket( sockfd, readMsg , textSize + 1 ) ; 

        if( 0 == valid ) {
            this->text = "";
        } else {
            this->text = readMsg ;
        }

        return valid;
    }

    public: int writeMessage( int sockfd ) {
        int valid = this->writeHead( sockfd ) ; 
        if( valid ) {
            valid = this->writeBody( sockfd );
        }

        return valid ; 
    }

    public: int writeHead( int sockfd ) {
        this->textSize = this->text.length();

        int valid = this->writeDataOnSocket( sockfd, & this->textSize, sizeof( this->textSize ) );

        return valid;
    }

    // write a message
    private: int writeBody( int sockfd ) {
        int valid = 0 ; 
        valid = this->writeTextOnSocket( sockfd, this->text.c_str() );      

        return valid ;
    }

    private: int writeDataOnSocket( int sockfd, void * data , const int size ) {
        int twn = 0 ;
        int wn = 0 ;
        char * buff = (char *) data ;
        do {  
            buff += wn ; 
            wn = write( sockfd, buff, size - twn );
            twn  += wn;
        } while ( -1 < wn && twn < size );

        return wn ; 
    }

    // write a message to the client
    private: int writeTextOnSocket( int sockfd, const char * sendMsg ) {        
        int valid = this->writeDataOnSocket( sockfd, (void *) sendMsg, strlen( sendMsg ) + 1 );
        
        return valid ;
    }

} ; 
// -- 