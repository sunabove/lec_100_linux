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

    ChatRoom * chatRoom ;

    public: Socket() ;

    // read a client message
    public: OpCodeMsg readOpCode() ;

    // write a message
    public: void writeOpCode( OpCodeMsg * opCodeMsg ) ;

} ;

// --
