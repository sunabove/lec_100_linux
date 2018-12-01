#pragma once

#include "OpCode.h"

class OpCodeExit : public OpCode {
    public :
        unsigned char    exitCode ;

    public: OpCodeExit() ;

    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
