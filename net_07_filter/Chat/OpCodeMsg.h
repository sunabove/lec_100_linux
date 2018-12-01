#pragma once

#include "OpCode.h"

class OpCodeMsg : public OpCode {
    public :
        std::string  text ;

    public: OpCodeMsg() ;
    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
