#include "Socket.h"
#include "OpCodeMsg.h"

Socket::Socket() {
    this->valid = false ;
}

OpCode * Socket::readOpCode( ) {
    OpCode * opCode = NULL ;

    opCode = new OpCodeMsg();

    int valid = opCode->readOpCode( this->sockfd );

    opCode->clientId = clientId ;

    this->valid = valid ;

    return opCode ;
}

int Socket::writeOpCode( OpCode * opCode ) {

    this->valid = opCode->writeOpCode( this->sockfd );

    return this->valid ;
}

//
