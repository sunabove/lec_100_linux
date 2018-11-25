#include "OpCodeSysInfo.h"

OpCodeSysInfo::OpCodeSysInfo() : OpCode( OP_CODE_SYS_INFO ) {
    this->sysMessage = "" ;
}

int OpCodeSysInfo::readBody( int sockfd ) {
    return this->readString( sockfd, & this->sysMessage );
}

int OpCodeSysInfo::writeBody( int sockfd ) {
    return this->writeString( sockfd, & this->sysMessage );
}
