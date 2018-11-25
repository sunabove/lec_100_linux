#include "Socket.h"

Socket::Socket() {
    this->valid = false ;
}

OpCodeMsg Socket::readOpCode( ) {
    OpCodeMsg opCodeMsg ;
    int valid = opCodeMsg.readOpCode( this->sockfd );

    opCodeMsg.clientId = clientId ;

    this->valid = valid ;

    return opCodeMsg;
}

void Socket::writeOpCode( OpCodeMsg * opCodeMsg ) {

    std::string textOrg = opCodeMsg->getText() ;

    if( opCodeMsg->clientId == this->clientId ) {
        opCodeMsg->setText( "*" + textOrg );
    }

    int valid = opCodeMsg->writeOpCode( this->sockfd );

    opCodeMsg->setText( textOrg );

    this->valid = valid ;
}

//
