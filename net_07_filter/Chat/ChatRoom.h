#pragma once

#include <vector>
#include <queue>
#include "OpCode.h"
#include "Socket.h"

class ChatRoom {
    public:
    FILE * console ;
    int valid ;
    std::vector<Socket * > sockets ;
    std::queue<OpCode *> opCodes;
    bool sendingOpCodes = false ;
    
    public:
    ChatRoom() ;

    void appendOpCode( OpCode * opCode ) ;
    
} ;
