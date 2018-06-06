/* A simple client */
#include <stdio.h>

#include "Socket.h"

void * readMessageThread( void * args );  
void * writeMessageThread( Socket * socket );  

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

    Socket socket;
    socket.sockfd     = sockfd;
    socket.valid      = 1 ; 
    socket.console    = console ; 

    pthread_t readThread ;
    pthread_create (&readThread, NULL, readMessageThread, & socket ); 

    writeMessageThread( & socket ); 

    /*  Wait for the threads to exit. */
   	pthread_join (readThread, NULL);

    fprintf( console, "\nGood bye!\n" );

    return 0;
}

void * writeMessageThread( Socket * socket ) { 
    FILE * console  = socket->console     ;
    int sockfd      = socket->sockfd      ;

    fprintf( console, "\n%s\n", "Writing Thread started." );
    fflush( console );    

    int wn ; 
    char buff[1024 + 1];  

    while( socket->valid ) {
        //fprintf( console, "Please enter the message: ");
        //fflush( console );
        bzero( buff, sizeof( buff ) );
        fgets( buff, sizeof( buff ), stdin );

        if( 'q' == buff[0] || 'Q' == buff[0] ) {
            socket->valid = 0 ; 
        }

        wn = write( sockfd, buff, strlen(buff) );

        if ( 0 > wn ) {
            socket->valid = 0 ;
            perror("ERROR writing to socket");
        } 
    }

    return 0;
}

void * readMessageThread( void * args ) { 
    Socket * socket = (Socket *) args ; 
    FILE * console  = socket->console  ;  
    int sockfd      = socket->sockfd   ;
    
    fprintf( console, "\n%s\n", "Reading Thread started." );
    fflush( console );

    size_t readMsgCount = 0 ; 
    while( socket->valid  ) { 
        bool doLog = false ; 
        if( doLog ){
            fprintf( console, "\n[%03zu] Reading a line ..." , readMsgCount );
            fflush( console );
        }

        int rn = 0 ; 
        // read a line 
        char readMsg[1024 + 1]; 
        if( socket->valid ) {
            bzero( readMsg, sizeof( readMsg ));
            char * buff = readMsg ;
            do { 
                buff += rn ; 
                rn = read( sockfd, buff, 1 );
            } while( socket->valid  && -1 <rn && '\n' != *buff );
            // -- read a line
        }

        if( doLog ) {
            fprintf( console, " done\n" );
            fflush( console );
        }

        if ( 0 > rn ) {
            socket->valid = 0 ; 
            perror("ERROR reading from socket");
        } else if( 0 < rn ) {
            readMsgCount ++;
            fprintf( console, "%s", readMsg );
            fflush( console );

            if( 1 == readMsgCount ) {
                fprintf( console, "\nEnter a message: ");
                fflush( console );        
            }
        }
    }

    return 0 ;
}

// -- 