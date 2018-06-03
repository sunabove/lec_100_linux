/* A simple server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <list>

class ClientSocket  {
    public: 
        bool closed ;
        int sockfd;
        int clientId ;
        const char * appName ; 
        void * clientSocketListPtr ; 

    public:
        ClientSocket() {
            this->closed = false ; 
        }
} ;

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
    int clientId = 0;

    listen(serverSockFd, 5);

    //std::list<ClientSocket * > clientSocketList ; 
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
            clientSocket.appName = appName ;
                
            pthread_t thread ;
            pthread_create (&thread, NULL, chatWithClient, &clientSocket );             
        }
    }
    
    return 0;
}

// read a client message
int readClientMessage( int sockfd , char * readMsg ) {
    int rn = 0 ; 
    char * buff = readMsg;
    do {
        buff += rn ;
        rn = read(sockfd, buff, 1);
    } while( -1 < rn && '\n' != *buff );

    return rn ;
}

// write a message to the client
int writeClientMessage( int sockfd, char * sendMsg ) {
    const int msgLen = strlen( sendMsg );
    int wn = 0 , twn = 0 ;
    char * buff = sendMsg ;
    do {  
        twn  += wn; 
        buff += wn ; 
        wn = write( sockfd, buff, msgLen - twn );        
    } while ( -1 < wn && twn < msgLen );

    if ( 0 < msgLen && '\n' != sendMsg[ msgLen -1 ] ) { 
        wn += write( sockfd , "\n", 1 );
    }

    return wn;
}

// There is a separate instance of this function for each connection.
void * chatWithClient( void * args ) { 
    FILE * console = stdout ;
    
    ClientSocket clientSocket = * ((ClientSocket *) args) ;
    const int sockfd        = clientSocket.sockfd      ;
    const int clientId      = clientSocket.clientId    ;
    const char * appName    = clientSocket.appName     ; 

    std::list<ClientSocket * > * clientSocketListPtr = (std::list<ClientSocket * > *) clientSocket.clientSocketListPtr ; 
    
    fprintf( console, "\nA Process(clientId = %03d) started.", clientId );

    int valid = 1 ;
    
    if( 1 ) {
        // send a welcome message to client.
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        snprintf ( sendMsg, sizeof(sendMsg), "Welcome to %s" , appName ); 
        int wn = writeClientMessage(sockfd, sendMsg );
        if (wn < 0) {
            valid = 0 ;
        }
        fprintf( console, "\nWelcome message sent." );
        fflush( console );
    }

    char readMsg[2048];

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
                fprintf(console, "Quit message.\n" );
                valid = 0 ; 
            } else { // send a response message.
                fprintf( console, "\n[%03d] A client message: %s", clientId, readMsg);
                fflush( console );
                
                char sendMsg [2048];
                bzero( sendMsg, sizeof(sendMsg) );
                snprintf ( sendMsg, sizeof(sendMsg), "Your message = %s", readMsg ); 

                fprintf(console, "\nMsg sent: %s" , sendMsg );
                fflush( console );

                int wn = 0 ; 
                wn = writeClientMessage( sockfd, sendMsg );                
                if (wn < 0) {
                    valid = 0 ; 
                }
            }
        }
    } 

    clientSocket.closed = 1 ; ; 
    close( sockfd );

    fprintf( console, "\nThe client(id = %03d) disconnected.\n", clientId );
    fflush( console );

    return 0;
}
// -- dostuff
// --