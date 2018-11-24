#pragma once

#include "OpCode.h"

class OpCodeMsg : public OpCode {
    private:
        unsigned int    textSize ;
        std::string     text ;

    public: OpCodeMsg() ;

    public: std::string & getText(); 
    public: void setText( std::string text ); 

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
