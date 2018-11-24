#pragma once

#include <vector>
#include "OpCodeMsg.h"
#include "Socket.h"

class ChatRoom {
    public:
        FILE * console ;
        int valid ;
        std::vector<Socket * > sockets ;
    
    public:
    ChatRoom() ;

    void appendOpCode( OpCodeMsg * opCodeMsg ) ;
    
} ;
