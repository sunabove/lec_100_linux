#include "OpCodeExit.h"

OpCodeExit::OpCodeExit() : OpCode( OP_CODE_EXIT )  {
    this->exitCode = 0 ; 
}

DataLength OpCodeExit::getBodySize() {
    DataLength len = 0 ;

    len += sizeof( exitCode );

    return len ;
}

int OpCodeExit::readBody( int sockfd ) {
    int valid = 1; 

    valid = valid and this->readDataOnSocket( sockfd, & this->exitCode , sizeof( exitCode ) ) ;

    return valid;
}

int OpCodeExit::writeBody( int sockfd ) {
    int valid = 1 ; 

    valid = valid and this->writeDataOnSocket( sockfd, & this->exitCode, sizeof( exitCode ) );

    return valid ;
}
