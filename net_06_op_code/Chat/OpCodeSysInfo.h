#pragma once

#include "OpCode.h"

class OpCodeSysInfo : public OpCode {
    private :
        std::string     sysMessage ;

    public: OpCodeSysInfo() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
