#pragma once

#include "OpCode.h"

class OpCodeNack : public OpCode {
    public :
        SeqNo   recvSeqNo ;
        Code    recvOpCode ;
        Code    recvErrCode ;

    public: OpCodeNack() ;

    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
