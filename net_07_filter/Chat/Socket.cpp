#include "Socket.h"
#include "OpCodeMsg.h"
#include "OpCodeSysInfo.h"
#include "OpCodeExit.h"

Socket::Socket() {
    this->valid = false ;
}

OpCode * Socket::readOpCode( ) {
    ZF_LOGI( "Reading an opCode ....." );

    OpCode * opCode = NULL ;

    unsigned char code ;
    char * buff = (char *)( & code ) ;
    int trn = 0 ;
    int rn = 0 ;
    const int size = sizeof( unsigned char );
    do {
        rn = read( sockfd, buff, size - trn );
        buff += rn ;
        trn  += 1 > rn ? 0 : rn ;
    } while ( -1 < rn && trn < size );

    ZF_LOGI( "code = %d", code );

    if( size == trn ) {
        if( OP_CODE_MSG == code ) {
            opCode = new OpCodeMsg();
        } else if ( OP_CODE_SYS_INFO == code ) {
            opCode = new OpCodeSysInfo();
        } else if( OP_CODE_EXIT == code ) {
            opCode = new OpCodeExit();
        }

        if( NULL != opCode ) {
            opCode->code = code ;

            int valid = opCode->readOpCode( this->sockfd );

            opCode->clientId = clientId ;

            this->valid = valid ;
        }
    }

    return opCode ;
}

int Socket::writeOpCode( OpCode * opCode ) {

    this->valid = opCode->writeOpCode( this->sockfd );

    return this->valid ;
}

//
