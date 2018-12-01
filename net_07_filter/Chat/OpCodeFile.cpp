#include "OpCodeFile.h"

OpCodeFile::OpCodeFile() : OpCode( OP_CODE_FILE ) {
    this->fileData = NULL ;
}

OpCodeFile::~ OpCodeFile() {
    if( NULL != this->fileData ) {
        delete [] this->fileData ;
    }
}

DataLength OpCodeFile::getBodySize() {
    DataLength len = 0 ;

    len += sizeof( fileSeqNo );
    len += sizeof( fileTotalSize );
    len += sizeof( fileDataSize );
    len += sizeof( fileData );

    return len ;
}

int OpCodeFile::readBody( int sockfd ) {
    int valid = 1;

    valid = valid and this->readDataOnSocket( sockfd, & fileSeqNo , sizeof( fileSeqNo ) ) ;
    valid = valid and this->readDataOnSocket( sockfd, & fileTotalSize , sizeof( fileTotalSize ) ) ;
    valid = valid and this->readDataOnSocket( sockfd, & fileDataSize , sizeof( fileDataSize ) ) ;

    this->fileData = new unsigned char[ fileDataSize ];

    valid = valid and this->readDataOnSocket( sockfd, this->fileData , this->fileDataSize ) ;

    return valid;
}

int OpCodeFile::writeBody( int sockfd ) {
    int valid = 1 ;

    if( NULL == fileData ) {
        fileDataSize = 0 ;
    }else if( NULL != fileData ) {
        fileDataSize = sizeof( fileData );
    }

    valid = valid and this->writeDataOnSocket( sockfd, & fileSeqNo, sizeof( fileSeqNo ) );
    valid = valid and this->writeDataOnSocket( sockfd, & fileTotalSize, sizeof( fileTotalSize ) );
    valid = valid and this->writeDataOnSocket( sockfd, & fileDataSize, sizeof( fileDataSize ) );

    if( 0 < fileDataSize ) {
        valid = valid and this->writeDataOnSocket( sockfd, fileData, sizeof( fileData ) );
    }

    return valid ;
}
