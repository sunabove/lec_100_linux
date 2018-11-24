#pragma once

#include <string.h> 
#include <unistd.h>

#include <string>

class OpCode {
    public:
        // header
        unsigned char    flowControl ;
        unsigned char    opCode ;
        unsigned int     seqNo ;
        unsigned char    contLast ; // C/L
        unsigned int     date ;
        unsigned int     clientId ;
        unsigned int     bodySize ;

    public: OpCode() {
        this->flowControl = 0x00 ;
        this->opCode = 0x00 ;
        this->seqNo = 0x00;
        this->contLast = 0x00;
        this->date = 0x00;
        this->clientId = 0x00 ;
        this->bodySize = 0x00;
    }

    public: int readDataOnSocket( int sockfd, void * data , const int size ) {
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

    public: int writeDataOnSocket( int sockfd, const void * data , const int size ) {
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

    public: int writeHead( int sockfd ) {
        int valid = 1 ;

        valid = valid and this->writeDataOnSocket( sockfd, & flowControl, sizeof( unsigned char ) );

        return valid;
    }

    public: int readHead( int sockfd ) {
        int valid = 1;
        valid = this->readDataOnSocket( sockfd, & this->flowControl , sizeof( unsigned char ) );

        return valid ;
    }

    // read a client message
    public: int readOpCode( int sockfd ) {
        int valid = 1;
        valid = valid && this->readHead( sockfd );
        valid = valid && this->readBody( sockfd );

        return valid ;
    }

    public: int writeOpCode( int sockfd ) {
        int valid = 1 ;

        valid = valid && this->writeHead( sockfd ) ;
        valid = valid && this->writeBody( sockfd ) ;

        return valid ;
    }

    public: virtual int readBody( int sockfd ) ;

    // write a message
    private: virtual int writeBody( int sockfd ) ;

} ; 
// -- 
