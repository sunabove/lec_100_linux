/* A simple client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

class ClientSocket {
    public:
        int sockfd ;
        int * validPtr ; 
        FILE * console ; 
};

void * startWriteThread( void * validPtr );  
void * startReadThread( void * validPtr );  

int main(int argc, char **argv) {
    FILE * console = stdout ; 
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    int portno = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket"); 
        exit( 1 );
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit( 1 );
    }

    int valid = 1 ; 

    ClientSocket clientSocket;
    clientSocket.sockfd     = sockfd;
    clientSocket.validPtr   = & valid ; 
    clientSocket.console    = console ; 

    pthread_t readThread ;
    pthread_create (&readThread, NULL, startReadThread, (void *) & clientSocket ); 

    pthread_t writeThread ;
    pthread_create (&writeThread, NULL, startWriteThread, (void *) & clientSocket ); 

    /*  Wait for the threads to exit. */
   	pthread_join (readThread, NULL);
   	pthread_join (writeThread, NULL);

    fprintf( console, "\nGood bye!\n" );

    return 0;
}

void * startWriteThread( void * args ) {
    ClientSocket * clientSocket = (ClientSocket *) args ; 
    FILE * console  = clientSocket->console     ; 
    int * validPtr  = clientSocket->validPtr    ; 
    int sockfd      = clientSocket->sockfd      ;

    fprintf( console, "\n%s\n", "Writing Thread started." );
    fflush( console );    

    int wn ; 
    char buff[1024 + 1];  

    while( * validPtr ) {
        fprintf( console, "Please enter the message: ");
        fflush( console );
        bzero( buff, sizeof( buff ) );
        fgets( buff, sizeof( buff ), stdin );

        if( 'q' == buff[0] ) {
            * validPtr = 0 ; 
        }

        wn = write(sockfd,buff,strlen(buff));

        if ( 0 > wn ) {
            * validPtr = 0 ;
            perror("ERROR writing to socket");
        } 
    }
}

void * startReadThread( void * args ) { 
    ClientSocket * clientSocket = (ClientSocket *) args ; 
    FILE * console  = clientSocket->console     ; 
    int * validPtr  = clientSocket->validPtr    ; 
    int sockfd      = clientSocket->sockfd       ;
    
    fprintf( console, "\n%s\n", "Reading Thread started." );
    fflush( console ); 
    
    char buff[1024 + 1];  

    int rn ; 
    while( *validPtr ) { 
        bzero(buff, sizeof( buff ));
        rn = read(sockfd,buff, sizeof( buff ) - 1 );
        if ( 0 > rn ) {
            *validPtr = 0 ; 
            perror("ERROR reading from socket");
        } else if( 0 < rn ) {
            fprintf( console, "%s\n",buff);
            fflush( console );
        }
    }
}

// -- 