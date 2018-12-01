/* A simple server */ 

#include "Server.h"
#include "OpCodeSysInfo.h"
 
Server::Server() {
}

// runServer
bool Server::runServer( const char * portNo ) {
    FILE * console = stdout ; 

    const char * LINE = "___________________________________________________\n" ;
    const char * appName = "HANSEI Linux Multi Chat Room System v1.0.1" ;

    fprintf( console, "%s", LINE );
    fprintf( console, "\n%s\n" , appName );
    fprintf( console, "%s\n", LINE );

    int serverSockFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSockFd < 0) {
        perror("ERROR opening socket");
        return false ;
    } 

    struct sockaddr_in servAddr;

    bzero((char *)&servAddr, sizeof(servAddr));
    int portno = atoi( portNo );
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portno);

    if (bind(serverSockFd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("ERROR on binding");
        exit( 1 );
    } else {
        fprintf( console, "Server port: %d\n" , portno );
    }

    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    
    listen(serverSockFd, 5);

    unsigned int clientId = 0;
    ChatRoom chatRoom ;
    chatRoom.console = console;

    while (1) {
        clientId ++;
        fprintf( console, "[%03d] Acceping a client connection...\n" , clientId );
        fflush( console );
        int clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if ( 0 > clientSockFd ) {
            fprintf( console, "[%03d] ERROR on accept\n" , clientId );
        } if ( 0 <= clientSockFd ) {
            fprintf( console, "[%03d] Accepted a client.\n" , clientId );

            Socket * socket = new Socket();
            socket->sockfd = clientSockFd ;
            socket->clientId = clientId ;
            socket->valid = true ; 
            socket->appName = appName ;
            socket->chatRoom = & chatRoom ; 

            chatRoom.sockets.push_back( socket ) ; 
                
            pthread_t thread ;
            pthread_create (&thread, NULL, chatWithClientThread, socket );             
        }
    }
    
    return true ;
}
// -- runServer

// There is a separate instance of this function for each connection.
void * Server::chatWithClientThread( void * args ) {
    Socket * socket         = (Socket *) args       ; 
    
    const int clientId      = socket->clientId      ;
    const char * appName    = socket->appName       ; 
    ChatRoom * chatRoom     = socket->chatRoom      ;

    auto console = stdout ;

    ZF_LOGI( "A Process(clientId = %03d) started.\n", clientId );

    if( socket->valid ) {
        auto valid = true ; 
        if( valid ) {  
            // send a welcome message to client.
            char welcomeMsg [2048];
            bzero( welcomeMsg, sizeof(welcomeMsg) );
            snprintf ( welcomeMsg, sizeof(welcomeMsg), "Welcome to %s" , appName ); 
            
            // send sysinfo message
            OpCodeSysInfo opCodeSysInfo ;
            opCodeSysInfo.clientId = clientId ; 

            opCodeSysInfo.sysMessage = welcomeMsg ; 
            socket->writeOpCode( & opCodeSysInfo );

            ZF_LOGI( "Welcome message sent.\n" ); 
        }
        
        if( valid ) {  
            OpCodeMsg opCodeMsg ;
            opCodeMsg.clientId = clientId ; 
            opCodeMsg.text = "Enter a message" ; 
            socket->writeOpCode( & opCodeMsg );

            ZF_LOGI( "Enter message sent.\n" ); 
        }
        
    }

    while( socket->valid ) {
        OpCode * opCode = socket->readOpCode( ); 

        if( NULL == opCode ) {
            ZF_LOGI( "OPCODE IS NULL." );
        } else if ( false == socket->valid ) {
            ZF_LOGI( "[%03d] ERROR: reading from socket\n", clientId ); 
        } else if( socket->valid ) {

            auto code = opCode->code ;

            ZF_LOGI( "opCode = %d", code );

            if( OP_CODE_MSG == code ) { 
                // close socket
                OpCodeMsg * opCodeMsg = (OpCodeMsg * ) opCode ;
                ZF_LOGI( "[%03d] A client message: %s\n", clientId, opCodeMsg->text.c_str() );
                
                chatRoom->appendOpCode( opCode ); 
            } else if ( OP_CODE_EXIT == code ) {
                // close socket   
                fprintf( console, "[%03d] client has exited.\n" , clientId ); 

                socket->valid = false ; 
            }
        } 
    } 

    socket->valid = false ;  

    close( socket->sockfd );

    ZF_LOGI( "The client(id = %03d) disconnected.\n", clientId ); 

    return 0;
}
// -- chatWithClientThread 

// main
int main(int argc, char **argv) { 

    const char * portNo = 2 > argc ? "100" : argv[1];
    Server server ;
    return server.runServer( portNo ); 
} 
// -- main
