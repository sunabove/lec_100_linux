#include "ChatRoom.h"

ChatRoom::ChatRoom() {
    this->console = stdout;
    this->valid = 1 ;
    this->sendingOpCodes = false ;
}

void ChatRoom::appendOpCode( OpCode * opCodeInsert ) {

    std::queue<OpCode *> & opCodes = this->opCodes ;

    opCodes.push( opCodeInsert );

    if( sendingOpCodes ) {
        ZF_LOGI( "SendingOpCodes now..... skipped send manually." );
    }

    std::vector<Socket* > & sockets = this->sockets ;

    // removes invalid sockets
    for( auto it = sockets.begin() ; it != sockets.end() ; ) {
        Socket * socket = *it ;
        if( false == socket->valid ) {
            fprintf( console, "The client(id = %03d) is invalid. \n" , socket->clientId );
            fflush( console );
            delete socket ;
            it = sockets.erase( it );
        } else {
            it ++ ;
        }
    }
    // -- removes invalid sockets

    fprintf( console, "Client count = %03zu \n" , sockets.size() );
    fflush( console );

    while( 0 < opCodes.size() ) {
        OpCode * opCode = opCodes.front();

        // send message to clients
        for( auto & socket : sockets ) {
            socket->writeOpCode( opCode );

            fprintf(console, "Msg sent to client(%03d): \n" , socket->clientId );
            fflush( console );

        }
        // -- send message to clients

        opCodes.pop();
    }
}
