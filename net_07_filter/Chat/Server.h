/* A simple server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <vector>
#include <string>

#include "OpCode.h"
#include "OpCodeMsg.h"
#include "Socket.h"
#include "ChatRoom.h"

class Server { 
    public:
        Server();

    // runServer
    bool runServer( const char * portNo );

    // There is a separate instance of this function for each connection.
    public: static void * chatWithClientThread( void * args );
};
// --
