#include "OpCodeExit.h"

OpCodeExit::OpCodeExit() {
    this->exitCode = 0 ; 
}

int OpCodeExit::readBody( int sockfd ) {
    int valid = 1; 

    valid = this->readDataOnSocket( sockfd, & this->exitCode , sizeof( exitCode ) ) ; 

    return valid;
}

int OpCodeExit::writeBody( int sockfd ) {
    int valid = 1 ; 

    valid = this->writeDataOnSocket( sockfd, & this->exitCode, sizeof( exitCode ) );

    return valid ;
}
