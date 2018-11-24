#pragma once

#include <string.h> 
#include <unistd.h>

#include <string>

class OpCode {
    public:
        // header
        unsigned char    opCode ;
        unsigned int     seqNo ;
        unsigned char    flowControl ;
        unsigned char    contLast ; // C/L
        unsigned int     date ;
        unsigned int     clientId ;
        unsigned int     bodySize ;

    public: OpCode();
            virtual ~ OpCode() ;

    public: int readDataOnSocket( int sockfd, void * data , const int size )  ;

    public: int writeDataOnSocket( int sockfd, const void * data , const int size ) ;

    public: int writeHead( int sockfd ) ;

    public: int readHead( int sockfd ) ;

    public: int readOpCode( int sockfd );

    public: int writeOpCode( int sockfd ) ;

    public: virtual int readBody( int sockfd ) = 0 ;

    private: virtual int writeBody( int sockfd ) = 0 ;

} ; 

//
