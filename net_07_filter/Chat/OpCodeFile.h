#pragma once

#include "OpCode.h"

class OpCodeFile : public OpCode {
    public :
        SeqNo fileSeqNo ;
        unsigned long fileTotalSize ;
        DataLength fileDataSize ;
        unsigned char * fileData ;

    public: OpCodeFile() ;
        virtual ~ OpCodeFile() ;

    public: virtual DataLength getBodySize() ;

    public: int readBody( int sockfd ) ;

    public: int writeBody( int sockfd ) ;

} ;
//
