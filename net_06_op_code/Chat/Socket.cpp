#include "Socket.h"

Socket::Socket() {
    this->valid = false ;
    this->console = stdout ;
}

OpCodeMsg Socket::readOpCode( ) {
    OpCodeMsg opCodeMsg ;
    int valid = opCodeMsg.readOpCode( this->sockfd );

    opCodeMsg.clientId = clientId ;

    this->valid = valid ;

    return opCodeMsg;
}

void Socket::writeOpCode( OpCodeMsg * opCodeMsg ) {

    std::string textOrg = opCodeMsg->text ;

    if( opCodeMsg->clientId == this->clientId ) {
        opCodeMsg->text = "*" + opCodeMsg->text ;
    }

    int valid = opCodeMsg->writeOpCode( this->sockfd );

    opCodeMsg->text = textOrg;

    this->valid = valid ;
}

//
