#include "OpCode.h"

OpCode::~OpCode() {
}

OpCode::OpCode(void) {
    this->opCode = 0x00 ;
    this->seqNo = 0x00;
    this->flowControl = 0x00 ;
    this->contLast = 0x00;
    this->date = 0x00;
    this->clientId = 0x00 ;
    this->bodySize = 0x00;
}

int OpCode::writeHead( int sockfd ) {
    int valid = 1 ;

    valid = valid and this->writeDataOnSocket( sockfd, & opCode, sizeof( opCode ) );
    valid = valid and this->writeDataOnSocket( sockfd, & seqNo, sizeof( seqNo ) );
    valid = valid and this->writeDataOnSocket( sockfd, & flowControl, sizeof( flowControl ) );
    valid = valid and this->writeDataOnSocket( sockfd, & contLast, sizeof( contLast ) );
    valid = valid and this->writeDataOnSocket( sockfd, & date, sizeof( date ) );
    valid = valid and this->writeDataOnSocket( sockfd, & clientId, sizeof( clientId ) );
    valid = valid and this->writeDataOnSocket( sockfd, & bodySize, sizeof( bodySize ) );

    return valid;
}

int OpCode::readHead( int sockfd ) {
    int valid = 1;

    valid = valid and this->readDataOnSocket( sockfd, & this->opCode , sizeof( opCode ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->seqNo , sizeof( seqNo ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->flowControl , sizeof( flowControl ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->contLast , sizeof( contLast ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->date , sizeof( date ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->clientId , sizeof( clientId ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->bodySize , sizeof( bodySize ) );

    return valid ;
}

int OpCode::readOpCode( int sockfd ) {
    int valid = 1;

    ZF_LOGW( "Reading an opCode ..." );
    valid = valid and this->readHead( sockfd );

    ZF_LOGI( "readBody" );
    valid = valid and this->readBody( sockfd );
    ZF_LOGW( "Deon. readBody" );

    return valid ;
}

int OpCode::writeOpCode( int sockfd ) {
    int valid = 1 ;

    ZF_LOGI( "Writing an opCode ..." );
    valid = valid and this->writeHead( sockfd ) ;
    ZF_LOGI( "writeBody" );
    valid = valid and this->writeBody( sockfd ) ;

    fsync( sockfd );

    ZF_LOGI( "Done. Writing an opCode." );

    return valid ;
}

int OpCode::readDataOnSocket( int sockfd, void * data , const int size ) {
    int trn = 0 ;
    int rn = 0 ;
    char * buff = (char *) data ;
    do {
        rn = read( sockfd, buff, size - trn );
        buff += rn ;
        trn  += rn;
    } while ( -1 < rn && trn < size );

    ZF_LOGW( "read data size = %d, trn = %d", size, trn );

    return rn ;
}

int OpCode::writeDataOnSocket( int sockfd, const void * data , const int size ) {
    int twn = 0 ;
    int wn = 0 ;
    char * buff = (char *) data ;
    do {
        buff += wn ;
        wn = write( sockfd, buff, size - twn );
        twn  += wn;
    } while ( -1 < wn && twn < size );

    ZF_LOGW( "write data size = %d, twn = %d", size, twn );

    return wn ;
}

