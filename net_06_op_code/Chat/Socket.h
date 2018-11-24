#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <vector>
#include <string>

#include "OpCodeMsg.h"

class ChatRoom ;

class Socket  {
    public: 

    int valid ; 
    int sockfd;
    unsigned int clientId ;
    const char * appName ;  
    FILE * console ;

    ChatRoom * chatRoom ;

    public: Socket() { 
        this->valid = false ;
        this->console = stdout ; 
    }

    // read a client message
    public: OpCodeMsg readOpCode( ) {
        OpCodeMsg opCodeMsg ;
        int valid = opCodeMsg.readOpCode( this->sockfd );

        opCodeMsg.clientId = clientId ;

        this->valid = valid ; 

        return opCodeMsg;
    }

    // write a message
    public: void writeOpCode( OpCodeMsg * opCodeMsg ) {
        
        std::string textOrg = opCodeMsg->text ;

        if( opCodeMsg->clientId == this->clientId ) {
            opCodeMsg->text = "*" + opCodeMsg->text ;
        } 

        int valid = opCodeMsg->writeOpCode( this->sockfd );

        opCodeMsg->text = textOrg;

        this->valid = valid ; 
    } 

} ;

// --
