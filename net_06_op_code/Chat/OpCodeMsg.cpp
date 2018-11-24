#include "zf_log.h"
#include "OpCodeMsg.h"

OpCodeMsg::OpCodeMsg() {
    this->text = "" ;
    this->textSize = 0 ;
}

std::string & OpCodeMsg::getText() {
    return this->text ; 
}

void OpCodeMsg::setText( std::string text ) {
    this->text = text ;
    this->textSize = text.size();
}

int OpCodeMsg::readBody( int sockfd ) {
    int valid = 1; 

    valid = valid and this->readDataOnSocket( sockfd, & this->textSize , sizeof( textSize ) ) ;

    char readMsg[ textSize + 1 ];
    bzero( readMsg, sizeof( readMsg ));

    valid = valid and this->readDataOnSocket( sockfd, readMsg , textSize ) ;

    if( 0 == valid ) {
        this->text = "";
    } else {
        this->text = readMsg ;
    }

    return valid;
}

int OpCodeMsg::writeBody( int sockfd ) {
    int valid = 1 ;

    this->textSize = this->text.size();

    valid = valid and this->writeDataOnSocket( sockfd, & textSize, sizeof( textSize ) );

    const char * str = this->text.c_str();

    ZF_LOGI( "str = %s, len = %d", str, strlen( str ) );

    valid = valid and this->writeDataOnSocket( sockfd, str, strlen( str ) );

    fsync( sockfd );

    return valid ;
}
