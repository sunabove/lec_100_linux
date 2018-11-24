/* A simple server */ 

#include "Server.h"
 
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
        fprintf( console, "Server bindded on port(%d)[%d]\n" , portno, servAddr.sin_port );
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
            socket->console = console;
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
    
    FILE * console          = socket->console       ;
    const int clientId      = socket->clientId      ;
    const char * appName    = socket->appName       ; 
    ChatRoom * chatRoom     = socket->chatRoom      ;

    fprintf( console, "A Process(clientId = %03d) started.\n", clientId );

    if( socket->valid ) {
        // send a welcome message to client.
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        snprintf ( sendMsg, sizeof(sendMsg), "Welcome to %s" , appName ); 
        
        OpCodeMsg opCodeMsg ;
        opCodeMsg.text = sendMsg ;
        opCodeMsg.text = opCodeMsg.text.size();
        opCodeMsg.clientId = clientId ;

        socket->writeOpCode( & opCodeMsg );
        opCodeMsg.text = "Enter a message";
        opCodeMsg.text = opCodeMsg.text.size();
        socket->writeOpCode( & opCodeMsg );

        fprintf( console, "Welcome message sent.\n" );
        fflush( console );
    }

    while( socket->valid ) {
        OpCodeMsg opCodeMsg = socket->readOpCode( ); 

        if ( false == socket->valid ) {
            fprintf(console,"[%03d] ERROR: reading from socket\n", clientId);
            fflush( console );
        } else if( socket->valid ) {
            if( 0 < opCodeMsg.text.size() && 'q' == opCodeMsg.text.c_str()[0] ) { // quit this chatting.
                fprintf(console, "Quit message.\n" );
            } else { // send a response message.
                fprintf( console, "[%03d] A client message: %s\n", clientId, opCodeMsg.text.c_str() );
                fflush( console );

                chatRoom->appendOpCode( & opCodeMsg );
            }
        }
    } 

    socket->valid = false ;  

    close( socket->sockfd );

    fprintf( console, "The client(id = %03d) disconnected.\n", clientId );
    fflush( console );

    return 0;
}
// -- chatWithClientThread 

int main(int argc, char **argv) { 

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    } else {
        const char * portNo = argv[1];
        Server server ;
        server.runServer( portNo );
    }
    
    return 0;
} 
//
