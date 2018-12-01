#include "OpCode.h"

OpCode::~OpCode() {
    this->flowControl = 0x01 ;
}

OpCode::OpCode( unsigned int code ) {
    this->code = code ;
    this->seqNo = 0x00;
    this->flowControl = 0x00 ;
    this->contLast = 0x00;
    this->date = 0x00;
    this->clientId = 0x00 ;
    this->bodySize = 0x00;
}

DataLength OpCode::getHeaderSize() {
    DataLength len = 0 ;

    len += sizeof( code );
    len += sizeof( bodySize );
    len += sizeof( seqNo );
    len += sizeof( flowControl );
    len += sizeof( contLast );
    len += sizeof( clientId );
    len += sizeof( date );

    return len ;
}

int OpCode::writeHead( int sockfd ) {
    int valid = 1 ;

    valid = valid and this->writeDataOnSocket( sockfd, & code, sizeof( code ) );

    valid = valid and this->writeDataOnSocket( sockfd, & flowControl, sizeof( flowControl ) );
    valid = valid and this->writeDataOnSocket( sockfd, & contLast, sizeof( contLast ) );

    valid = valid and this->writeDataOnSocket( sockfd, & bodySize, sizeof( bodySize ) );
    valid = valid and this->writeDataOnSocket( sockfd, & date, sizeof( date ) );

    valid = valid and this->writeDataOnSocket( sockfd, & seqNo, sizeof( seqNo ) );
    valid = valid and this->writeDataOnSocket( sockfd, & clientId, sizeof( clientId ) );

    return valid;
}

int OpCode::readHead( int sockfd ) {
    int valid = 1;

    //valid = valid and this->readDataOnSocket( sockfd, & this->code , sizeof( code ) );

    valid = valid and this->readDataOnSocket( sockfd, & this->flowControl , sizeof( flowControl ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->contLast , sizeof( contLast ) );

    valid = valid and this->readDataOnSocket( sockfd, & this->bodySize , sizeof( bodySize ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->date , sizeof( date ) );

    valid = valid and this->readDataOnSocket( sockfd, & this->seqNo , sizeof( seqNo ) );
    valid = valid and this->readDataOnSocket( sockfd, & this->clientId , sizeof( clientId ) );

    return valid ;
}

int OpCode::readOpCode( int sockfd ) {
    int valid = 1;

    ZF_LOGI( "Reading an opCode ..." );

    ZF_LOGI( "readHead" );
    valid = valid and this->readHead( sockfd );
    ZF_LOGI( "Done. readHead" );

    ZF_LOGI( "readBody" );
    valid = valid and this->readBody( sockfd );
    ZF_LOGI( "Deon. readBody" );

    ZF_LOGI( "Deon. reading an opCode." );

    return valid ;
}

int OpCode::writeOpCode( int sockfd ) {
    int valid = 1 ;

    ZF_LOGI( "Writing an opCode ..." );

    this->bodySize = this->getBodySize();

    ZF_LOGI( "writeHead" );
    valid = valid and this->writeHead( sockfd ) ;
    ZF_LOGI( "Done. writeHead" );

    ZF_LOGI( "writeBody" );
    valid = valid and this->writeBody( sockfd ) ;
    ZF_LOGI( "Deon. writeBody" );

    fsync( sockfd );

    ZF_LOGI( "Done. Writing an opCode." );

    return valid ;
}

int OpCode::readString( int sockfd, std::string * text ) {
    int valid = 1;

    DataLength textSize = 0 ;

    valid = valid and this->readDataOnSocket( sockfd, & textSize , sizeof( textSize ) ) ;

    if( 0 < textSize ) {
        char readMsg[ textSize + 1 ];
        bzero( readMsg, sizeof( readMsg ));

        valid = valid and this->readDataOnSocket( sockfd, readMsg , textSize ) ;

        (* text) = valid ? readMsg : "" ;
    } else {
        (* text) = "";
    }

    return valid;
}

int OpCode::writeString( int sockfd, const std::string * text ) {
    int valid = 1 ;

    const char * str = text->c_str();
    DataLength textSize = strlen( str );

    ZF_LOGI( "str = %s, len = %zu", str, strlen( str ) );

    valid = valid and this->writeDataOnSocket( sockfd, & textSize, sizeof( textSize ) );

    if( valid and 0 < textSize ) {
        valid = valid and this->writeDataOnSocket( sockfd, str, strlen( str ) );
    }

    return valid ;
}

int OpCode::readDataOnSocket( int sockfd, void * data , const int size ) {
    int trn = 0 ;

    if( 0 < size ) { 
        int rn = 0 ;
        char * buff = (char *) data ;
        do {
            rn = read( sockfd, buff, size - trn );
            buff += rn ;
            trn  += 1 > rn ? 0 : rn ;
        } while ( -1 < rn && trn < size );
    }

    ZF_LOGW( "read data size = %d, trn = %d", size, trn );

    return trn ;
}

int OpCode::writeDataOnSocket( int sockfd, const void * data , const int size ) {
    int twn = 0 ;
    
    if( 0 < size ) {
        int wn = 0 ;
        char * buff = (char *) data ;
        do {
            buff += wn ;
            wn = write( sockfd, buff, size - twn );
            twn  += 1 > wn ? 0 : wn ;
        } while ( -1 < wn && twn < size );
    }

    ZF_LOGW( "write data size = %d, twn = %d", size, twn );

    return twn ;
}

