#pragma once

/* A simple client */
#include <stdio.h>

#include "Socket.h"

int connect_socket (int domain, int type, int protocol) ;

class Client { 
    public : 
        Socket socket ;

    public : Client() ;

    public: virtual int processOpCode( OpCode * message ) = 0 ;

    public: int connectServer(const char * hostName , const char * portNo );

    public: static void * readMessageThread( void * args ) ;

    public: void readOpCode();
    
};

//
