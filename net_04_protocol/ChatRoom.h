#pragma once

#include <vector>
#include "Message.h"
#include "Socket.h"

class ChatRoom {
    public:
        FILE * console ;
        int valid ;
        std::vector<Socket * > sockets ; 
    private: 
    
    public:

    ChatRoom() {
        this->console = stdout; 
        this->valid = 1 ; 
    }

    void appendMessage( Message * message ) {
        std::vector<Socket* > * sockets = & this->sockets ;
        // removes invalid sockets
        for( auto it = sockets->begin() ; it != sockets->end() ; ) {
            Socket * socket = *it ; 
            if( false == socket->valid ) { 
                fprintf( console, "\nThe client(id = %03d) is invalid." , socket->clientId );
                fflush( console );
                delete socket ;
                it = sockets->erase( it );
            } else {
                it ++ ;
            } 
        }

        fprintf( console, "\nClient count = %03zu" , sockets->size() );
        fflush( console );

        for( auto & socket : * sockets ) {
            socket->writeMessage( message );

            fprintf(console, "\nMsg sent to client(%03d): %s" , socket->clientId, message->text.c_str() );
            fflush( console );

        }
    };
    
} ;

// --