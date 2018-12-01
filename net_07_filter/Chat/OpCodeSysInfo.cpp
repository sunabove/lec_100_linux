#include "OpCodeSysInfo.h"

OpCodeSysInfo::OpCodeSysInfo() : OpCode( OP_CODE_SYS_INFO ) {
    this->sysMessage = "" ;
}

DataLength OpCodeSysInfo::getBodySize() {
    DataLength len = 0 ;

    len += this->sysMessage.size();

    return len ;
}

int OpCodeSysInfo::readBody( int sockfd ) {
    return this->readString( sockfd, & this->sysMessage );
}

int OpCodeSysInfo::writeBody( int sockfd ) {
    return this->writeString( sockfd, & this->sysMessage );
}
