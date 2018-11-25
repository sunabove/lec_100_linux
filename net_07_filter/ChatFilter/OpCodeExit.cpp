#include "OpCodeExit.h"

OpCodeExit::OpCodeExit() : OpCode( OP_CODE_EXIT )  {
    this->exitCode = 0 ; 
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
