#include "zf_log.h"
#include "OpCodeMsg.h"

OpCodeMsg::OpCodeMsg() : OpCode( OP_CODE_MSG ) {
    this->text = "" ;
}

DataLength OpCodeMsg::getBodySize() {
    DataLength len = 0 ;

    len += this->text.size();

    return len ;
}

int OpCodeMsg::readBody( int sockfd ) {
    return this->readString( sockfd, & this->text );
}

int OpCodeMsg::writeBody( int sockfd ) {
    return this->writeString( sockfd, & this->text );
}
