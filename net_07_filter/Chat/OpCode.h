#pragma once

#include <string.h> 
#include <unistd.h>

#include <string>

#include "zf_log.h"

#define OP_CODE_SYS_INFO 0x04
#define OP_CODE_MSG  0x22
#define OP_CODE_FILE 0x24
#define OP_CODE_EXIT 0x26
#define OP_CODE_ACK  0xA0
#define OP_CODE_NACK  0xA1

#define SOH 0x01 // Start Of Heading

typedef unsigned char   Code ;
typedef unsigned short  DataLength ;
typedef unsigned int    SeqNo ;
typedef unsigned int    ClientId ;
typedef unsigned char   FlowControl ;
typedef unsigned char   ContLast ;
typedef unsigned int    DateType ;

class OpCode {

    public:
        // header
        Code        code ;
        SeqNo       seqNo ;
        FlowControl flowControl ;
        ContLast    contLast ; // C/L
        DateType    date ;
        ClientId    clientId ;
        DataLength   bodySize ;

    public: OpCode( unsigned int code );
            virtual ~ OpCode() ;

    public: DataLength getHeaderSize( ) ;

    public: virtual DataLength getBodySize() = 0 ;

    public: virtual int readBody( int sockfd ) = 0 ;

    public: virtual int writeBody( int sockfd ) = 0 ;

    public: int readDataOnSocket( int sockfd, void * data , const int size )  ;

    public: int writeDataOnSocket( int sockfd, const void * data , const int size ) ;

    public: int readString( int sockfd, std::string * text ) ;

    public: int writeString( int sockfd, const std::string * text ) ;

    public: int writeHead( int sockfd ) ;

    public: int readHead( int sockfd ) ;

    public: int readOpCode( int sockfd );

    public: int writeOpCode( int sockfd ) ;



} ; 

//
