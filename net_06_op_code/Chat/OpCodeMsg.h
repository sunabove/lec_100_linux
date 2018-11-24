#pragma once

#include "OpCode.h"

class OpCodeMsg : public OpCode {
    public:
    unsigned int    textSize ;
    std::string     text ;

    public: OpCodeMsg() {
        this->text = "" ;
        this->textSize = 0 ;
    }

    public: int readBody( int sockfd ) {
        int valid = 1;

        int textSize = this->textSize ;

        char readMsg[ textSize + 1 ];
        bzero( readMsg, sizeof( readMsg ));

        valid = this->readDataOnSocket( sockfd, readMsg , textSize ) ;

        if( 0 == valid ) {
            this->text = "";
        } else {
            this->text = readMsg ;
        }

        return valid;
    }

    // write a message
    private: int writeBody( int sockfd ) {
        int valid = 1 ;

        const char * str = this->text.c_str();
        valid = this->writeDataOnSocket( sockfd, str, strlen( str ) );

        fsync( sockfd );

        return valid ;
    }

} ;
//
