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

void * chatWithClient( void * args );  

class ChatRoom ;

class Message {
    public:
        int clientId ;
        std::string text ; 
} ; 

class Socket  {
    public: 

    bool valid ; 
    int sockfd;
    int clientId ;
    const char * appName ;  
    ChatRoom * chatRoom ; 
    FILE * console ;

    public:

    Socket() { 
        this->valid = 1; 
        this->console = stdout ; 
    }

    // read a client message
    int readClientMessage( char * readMsg ) {
        int sockfd = this->sockfd ; 
        int rn = 0 ; 
        char * buff = readMsg;
        do {
            buff += rn ;
            rn = read(sockfd, buff, 1);
        } while( -1 < rn && '\n' != *buff );

        return rn ;
    } 

    // write a message
    void writeMessage( Message * message ) {
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        message->text.c_str();
        const char * name = ( message->clientId == this->clientId ) ? "* " : "" ;  
        snprintf ( sendMsg, sizeof(sendMsg), "%s%s", name, message->text.c_str() ); 

        int wn = 0 ; 
        wn = this->writeClientMessage( sockfd, sendMsg );                
        if (wn < 0) {
            this->valid = false ; 
        }
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

        fprintf(console, "\nMsg sent to client(%03d): %s" , clientId, sendMsg );
        fflush( console );

        return wn;
    }

} ;

class ChatRoom {
    public:
        FILE * console ;
        int valid ;
        std::vector<Socket * > sockets ; 
    private: 
    
    public:

    ChatRoom() {
        this->console = stdout; 
        this->valid = 1 ; 
    }

    void appendMessage( Message * message ) {
        std::vector<Socket* > * sockets = & this->sockets ;
        // removes invalid sockets
        for( auto it = sockets->begin() ; it != sockets->end() ; ) {
            Socket * socket = *it ; 
            if( false == socket->valid ) { 
                fprintf( console, "\nThe client(id = %03d) is invalid." , socket->clientId );
                fflush( console );
                delete socket ;
                it = sockets->erase( it );
            } else {
                it ++ ;
            } 
        }

        fprintf( console, "\nClient count = %03zu" , sockets->size() );
        fflush( console );

        for( auto & socket : * sockets ) {
            socket->writeMessage( message );
        }
    };
    
} ;

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
    const int clientId          = socket->clientId    ;
    bool * validPtr             = & socket->valid     ; 
    const char * appName        = socket->appName     ; 
    ChatRoom * chatRoom   = socket->chatRoom  ;

    fprintf( console, "\nA Process(clientId = %03d) started.", clientId );

    if( *validPtr ) {
        // send a welcome message to client.
        char sendMsg [2048];
        bzero( sendMsg, sizeof(sendMsg) );
        snprintf ( sendMsg, sizeof(sendMsg), "Welcome to %s" , appName ); 
        int wn = socket->writeClientMessage(sockfd, sendMsg );
        if (wn < 0) {
            *validPtr = false ;
        }
        fprintf( console, "\nWelcome message sent." );
        fflush( console );
    }

    char readMsg[2048];

    while( *validPtr ) {
        bzero(readMsg, sizeof(readMsg));

        // read a line
        int rn = socket->readClientMessage( readMsg ); 

        if ( 0 > rn ) {
            *validPtr = false ; 
            fprintf(console,"\n[%03d] ERROR: reading from socket", clientId);
            fflush( console );
            exit(1);
        } else if( -1 < rn ) {
            if( 'q' == readMsg[0] ) { // quit this chatting.
                fprintf(console, "Quit message.\n" );
                *validPtr = false ; 
            } else { // send a response message.
                fprintf( console, "\n[%03d] A client message: %s", clientId, readMsg);
                fflush( console );
                
                Message message ;
                message.clientId = clientId ; 
                message.text = readMsg ;

                chatRoom->appendMessage( & message );
            }
        }
    } 

    *validPtr = false ;  

    close( sockfd );

    fprintf( console, "\nThe client(id = %03d) disconnected.\n", clientId );
    fflush( console );

    return 0;
}
// -- dostuff
// --