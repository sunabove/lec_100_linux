#pragma once

#include "OpCode.h"

class OpCodeAck : public OpCode {
    public :
        SeqNo   recvSeqNo ;
        Code    recvOpCode ;

    public: OpCodeAck() ;

    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
