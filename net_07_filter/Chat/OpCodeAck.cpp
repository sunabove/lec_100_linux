#include "OpCodeAck.h"

OpCodeAck::OpCodeAck() : OpCode( OP_CODE_ACK )  {

}

DataLength OpCodeAck::getBodySize() {
    DataLength len = 0 ;

    len += sizeof( recvSeqNo );
    len += sizeof( recvOpCode );

    return len ;
}

int OpCodeAck::readBody( int sockfd ) {
    int valid = 1; 

    valid = valid and this->readDataOnSocket( sockfd, & this->recvSeqNo , sizeof( recvSeqNo ) ) ;
    valid = valid and this->readDataOnSocket( sockfd, & this->recvOpCode , sizeof( recvOpCode ) ) ;

    return valid;
}

int OpCodeAck::writeBody( int sockfd ) {
    int valid = 1 ; 

    valid = valid and this->writeDataOnSocket( sockfd, & this->recvSeqNo, sizeof( recvSeqNo ) );
    valid = valid and this->writeDataOnSocket( sockfd, & this->recvOpCode, sizeof( recvOpCode ) );

    return valid ;
}
