/* A simple server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

typedef struct  {
    int sockfd;
    int clientId ;
} ClientSocket ;

void * start_thread( void * args );  

int main(int argc, char **argv) {
    FILE * console = stdout ; 

    const char * LINE = "___________________________________________________\n" ; 
    fprintf( console, "%s", LINE );
 	fprintf( console, "\nHANSEI Linux chat system v1.0" );
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
    int clientAddrSize = sizeof(clientAddr);
    int clientId = 0;

    listen(serverSockFd, 5);
    while (1) {
        clientId ++;
        fprintf( console, "\n[%03d] Acceping a client connection...\n" , clientId );
        fflush( console );
        int clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if ( 0 > clientSockFd ) {
            perror("ERROR on accept");
	    } if ( 0 <= clientSockFd ) {
            ClientSocket clientSocket ;
            clientSocket.sockfd = clientSockFd ;
            clientSocket.clientId = clientId ;

            pthread_t thread ;
            pthread_create (&thread, NULL, start_thread, (void *) &clientSocket );
        }
    }
    return 0;
}

// read a client message
int readClientMessage( int sockfd , char * buff ) {
    int rn = 0 ; 
    do {
        buff += rn ;
        rn = read(sockfd, buff, 1);
    } while( -1 < rn && '\n' != *buff );

    return rn ;
}

int writeClientMessage( int sockfd, char * sendMsg , int msgLen ) {
    int wn = write(sockfd, sendMsg, msgLen );
    return wn;
}

/* There is a separate instance of this function for each connection. */

void * start_thread( void * args ) { 
    FILE * console = stdout ;
    
    ClientSocket * clientSocket = (ClientSocket *) args ;
    const int sockfd = clientSocket->sockfd;
    const int clientId = clientSocket->clientId ;
    
    fprintf( console, "\nA thread(%03d) started.", clientId );

    int valid = 1 ;
    char readMsg[2048];

    if( 1 ) {
        // send a welcome message to client.
        char sendMsg [2048];
        snprintf ( sendMsg, sizeof(sendMsg), "Welcome to HANSEI Linux Chat System v.10" ); 
        int wn = writeClientMessage(sockfd, sendMsg, strlen( sendMsg ));
        if (wn < 0) {
            valid = 0 ;
        }
    }

    while( valid ) {
        bzero(readMsg, sizeof(readMsg));

        // read a line
        int rn = readClientMessage( sockfd, readMsg ); 

        if ( 0 > rn ) {
            valid = 0 ; 
            fprintf(console,"\n[%03d] ERROR: reading from socket", clientId);
            fflush( console );
            exit(1);
        } else if( -1 < rn ) {
            if( 'q' == readMsg[0] ) { // quit this chatting.
                valid = 0 ; 
            } else { // send a response message.
                fprintf( console, "\n[%03d] A client message: %s", clientId, readMsg);
                fflush( console );
                char sendMsg [2048];
                snprintf ( sendMsg, sizeof(sendMsg), "[%03d] You have sent a message: %s", clientId, readMsg ); 
                int wn = writeClientMessage(sockfd, sendMsg, strlen( sendMsg ));
                if (wn < 0) {
                    valid = 0 ;
                }
            }
        }
    } 

    fprintf( console, "\nThe client(id = %03d) disconnected.\n", clientId );
    fflush( console );

    return clientSocket ;
}
// -- dostuff
// --