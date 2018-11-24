#include "OpCodeMsg.h"

OpCodeMsg::OpCodeMsg() {
    this->text = "" ;
    this->textSize = 0 ;
}

int OpCodeMsg::readBody( int sockfd ) {
    int valid = 1; 

    valid = this->readDataOnSocket( sockfd, & this->textSize , textSize ) ;

    char readMsg[ textSize + 1 ];
    bzero( readMsg, sizeof( readMsg ));

    valid = this->readDataOnSocket( sockfd, readMsg , textSize ) ;

    if( 0 == valid ) {
        this->text = "";
    } else {
        this->text = readMsg ;
    }

    return valid;
}

int OpCodeMsg::writeBody( int sockfd ) {
    int valid = 1 ;

    this->textSize = this->text.size();

    valid = this->writeDataOnSocket( sockfd, & textSize, sizeof( textSize ) );

    const char * str = this->text.c_str();

    valid = this->writeDataOnSocket( sockfd, str, strlen( str ) );

    fsync( sockfd );

    return valid ;
}
