#pragma once

#include <string.h> 
#include <unistd.h>

#include <string>

class Message {
    public:
        unsigned int clientId ;
        unsigned int textLen ;
        std::string text ; 
        bool valid ;

    public: Message() {
        this->valid = true ;
        this->text = "" ;
    } 
    
    public: Message(const Message & message) {
        this->clientId  = message.clientId;
        this->text      = message.text ;
        this->valid     = message.valid ;
    }

    // read a client message
    public: int readMessage( int sockfd ) {
        char readMsg[1024 + 1]; 
        bzero( readMsg, sizeof( readMsg )); 
        int rn = 0 ; 
        char * buff = readMsg;
        do {
            buff += rn ;
            rn = read(sockfd, buff, 1); 
        } while( this->valid && -1 < rn && '\n' != *buff );

        if( 0 > rn ) {
            this->valid = false;
            this->text = "";
        } else if( -1 < rn ) {
            this->valid = true ;
            this->text = readMsg ;
        }

        return this->valid ; 
    }

    // write a message
    public: int writeMessage( int sockfd ) {
        int wn = 0 ; 
        wn = this->writeMessageOnSocket( sockfd, this->text.c_str() );      

        if (wn < 0) {
            this->valid = false ; 
        }

        return this->valid ;
    }

    // write a message to the client
    private: int writeMessageOnSocket( int sockfd, const char * sendMsg ) {
        const int msgLen = strlen( sendMsg );
        int wn = 0 , twn = 0 ;
        char * buff = (char *) sendMsg ;
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