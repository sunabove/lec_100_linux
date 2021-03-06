#pragma once

#include "OpCode.h"

class OpCodeSysInfo : public OpCode {
    public :
        std::string     sysMessage ;

    public: OpCodeSysInfo() ;
    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
