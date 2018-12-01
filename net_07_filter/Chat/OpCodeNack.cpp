#include "OpCodeNack.h"

OpCodeNack::OpCodeNack() : OpCode( OP_CODE_NACK )  {

}

DataLength OpCodeNack::getBodySize() {
    DataLength len = 0 ;

    len += sizeof( recvSeqNo );
    len += sizeof( recvOpCode );
    len += sizeof( recvErrCode );

    return len ;
}

int OpCodeNack::readBody( int sockfd ) {
    int valid = 1; 

    valid = valid and this->readDataOnSocket( sockfd, & this->recvSeqNo , sizeof( recvSeqNo ) ) ;
    valid = valid and this->readDataOnSocket( sockfd, & this->recvOpCode , sizeof( recvOpCode ) ) ;
    valid = valid and this->readDataOnSocket( sockfd, & this->recvErrCode , sizeof( recvErrCode ) ) ;

    return valid;
}

int OpCodeNack::writeBody( int sockfd ) {
    int valid = 1 ; 

    valid = valid and this->writeDataOnSocket( sockfd, & this->recvSeqNo, sizeof( recvSeqNo ) );
    valid = valid and this->writeDataOnSocket( sockfd, & this->recvOpCode, sizeof( recvOpCode ) );
    valid = valid and this->writeDataOnSocket( sockfd, & this->recvErrCode, sizeof( recvErrCode ) );

    return valid ;
}
