/* A simple client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

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
    int n ; 
    char buff[1024 + 1];    

    if( 1 ) { // read server welcome message
        bzero(buff, sizeof( buff ));
        n = read(sockfd,buff, sizeof( buff ) - 1 );
        if ( 0 > n ) {
            valid = 0 ; 
            perror("ERROR reading from socket");
        } else if( 0 < n ) {
            fprintf( console, "%s\n",buff);
            fflush( console );
        }
    }

    while( valid ) {
        fprintf( console, "Please enter the message: ");
        fflush( console );
        bzero( buff, sizeof( buff ) );
        fgets( buff, sizeof( buff ), stdin );

        if( 'q' == buff[0] ) {
            valid = 0 ; 
        }

        n = write(sockfd,buff,strlen(buff));
        if ( 0 > n ) {
            valid = 0 ;
            perror("ERROR writing to socket");
        } else if ( valid && 0 < n ) {
            bzero(buff, sizeof( buff ));
            n = read(sockfd,buff, sizeof( buff ) - 1 );
            if ( 0 > n ) {
                valid = 0 ; 
                perror("ERROR reading from socket");
            } else if( 0 < n ) {
                fprintf( console, "%s\n",buff);
                fflush( console );
            }
        }
    }

    fprintf( console, "\nGood bye!\n" );

    return 0;
}