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

class Server {
    public: 
        const char * appName = "HANSEI Linux Multi Chat Room System v1.0" ;
    
    public:
        Server() {
        }

    bool runServer( const char * portNo ) {
        FILE * console = stdout ; 

        const char * LINE = "___________________________________________________\n" ; 
        fprintf( console, "%s", LINE );
        fprintf( console, "\n%s" , appName );
        fprintf( console, "\n%s", LINE );

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
        }

        struct sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientId = 0;

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
                pthread_create (&thread, NULL, chatWithClientThread, socket );             
            }
        }
        
        return true ;
    }

    // There is a separate instance of this function for each connection.
    public: static void * chatWithClientThread( void * args ) {
        Socket * socket         = (Socket *) args       ; 
        
        FILE * console          = socket->console       ;
        const int clientId      = socket->clientId      ;
        const char * appName    = socket->appName       ; 
        ChatRoom * chatRoom     = socket->chatRoom      ;

        fprintf( console, "\nA Process(clientId = %03d) started.", clientId );

        if( socket->valid ) {
            // send a welcome message to client.
            char sendMsg [2048];
            bzero( sendMsg, sizeof(sendMsg) );
            snprintf ( sendMsg, sizeof(sendMsg), "Welcome to %s" , appName ); 
            
            Message message ;
            message.text = sendMsg ;
            message.clientId = clientId ;

            socket->writeMessage( & message );
            message.text = "Enter a message";
            socket->writeMessage( & message );

            fprintf( console, "\nWelcome message sent." );
            fflush( console );
        }

        while( socket->valid ) {
            // read a line
            Message message = socket->readMessage( ); 

            if ( false == message.valid ) {
                socket->valid = false ; 
                fprintf(console,"\n[%03d] ERROR: reading from socket", clientId);
                fflush( console );
                exit(1);
            } else if( message.valid ) {
                if( 0 < message.text.size() && 'q' == message.text.c_str()[0] ) { // quit this chatting.
                    fprintf(console, "Quit message.\n" );
                    socket->valid = false ; 
                } else { // send a response message.
                    fprintf( console, "\n[%03d] A client message: %s", clientId, message.text.c_str() );
                    fflush( console );

                    chatRoom->appendMessage( & message );
                }
            }
        } 

        socket->valid = false ;  

        close( socket->sockfd );

        fprintf( console, "\nThe client(id = %03d) disconnected.\n", clientId );
        fflush( console );

        return 0;
    }
    // -- dostuff
};
// --