#pragma once

#include "OpCode.h"

class OpCodeMsg : public OpCode {
    public :
        std::string  text ;

    public: OpCodeMsg() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
