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

#include "Message.h"
#include "Socket.h"
#include "ChatRoom.h"

void * chatWithClient( void * args );  

const char * appName = "HANSEI Linux Multi Chat Room System v1.0" ;

int main(int argc, char **argv) {
    FILE * console = stdout ; 

    const char * LINE = "___________________________________________________\n" ; 
    fprintf( console, "%s", LINE );
 	fprintf( console, "\n%s" , appName );
	fprintf( console, "\n%s", LINE );

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    int serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSockFd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    struct sockaddr_in servAddr;

    bzero((char *)&servAddr, sizeof(servAddr));
    int portno = atoi(argv[1]);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portno);

    if (bind(serverSockFd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("ERROR on binding");
        exit( 1 );
    }

    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    unsigned int clientId = 0;

    listen(serverSockFd, 5);

    ChatRoom chatRoom ;
    chatRoom.console = console;

    while (1) {
        clientId ++;
        fprintf( console, "\n[%03d] Acceping a client connection...\n" , clientId );
        fflush( console );
        int clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if ( 0 > clientSockFd ) {
            perror("ERROR on accept");
	    } if ( 0 <= clientSockFd ) {
            Socket * socket = new Socket();
            socket->sockfd = clientSockFd ;
            socket->clientId = clientId ;
            socket->valid = true ;
            socket->console = console;
            socket->appName = appName ;
            socket->chatRoom = & chatRoom ; 

            chatRoom.sockets.push_back( socket ) ; 
                
            pthread_t thread ;
            pthread_create (&thread, NULL, chatWithClient, socket );             
        }
    }
    
    return 0;
}

// There is a separate instance of this function for each connection.
void * chatWithClient( void * args ) { 
    FILE * console = stdout ;
    
    Socket * socket = (Socket *) args ;
    const int sockfd            = socket->sockfd      ;
    const unsigned int clientId = socket->clientId    ;
    const char * appName        = socket->appName     ; 
    ChatRoom * chatRoom   = socket->chatRoom  ;

    fprintf( console, "\nA Process(clientId = %03d) started.", clientId );

    if( socket->valid ) {
        // send a welcome message to client.
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        snprintf ( sendMsg, sizeof(sendMsg), "Welcome to %s" , appName ); 
        socket->writeMessage( sendMsg );
        fprintf( console, "\nWelcome message sent." );
        fflush( console );
    }

    if( socket->valid ) {
        socket->writeMessage( "Enter a message: " );
    }

    while( socket->valid ) {
        // read a line
        Message messageRead = socket->readMessage( ); 

        if ( false == messageRead.valid ) {
            socket->valid = false ; 
            fprintf(console,"\n[%03d] ERROR: reading from socket", clientId);
            fflush( console );
            exit(1);
        } else if( true == messageRead.valid ) {
            if( 0 < messageRead.text.size() && 'q' == messageRead.text.c_str()[0] ) {
                // quit this chatting.
                fprintf(console, "Quit message.\n" );
                socket->valid = false ; 
            } else { 
                // send a response message.
                fprintf( console, "\n[%03d] A client message: %s", clientId, messageRead.text.c_str() );
                fflush( console );
                
                Message messageResponse ;
                messageResponse.clientId = clientId ; 
                messageResponse.text = messageRead.text ;

                chatRoom->appendMessage( & messageResponse );
            }
        }
    } 

    socket->valid = false ;  

    close( sockfd );

    fprintf( console, "\nA client(id = %03d) disconnected.\n", clientId );
    fflush( console );

    return 0;
}
// -- dostuff
// --