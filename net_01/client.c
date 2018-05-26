#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg) {
    perror(msg); 
}

int main(int argc, char *argv[]) {
    FILE * console = stdout ;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket"); 
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }
    int valid = 1 ;
    char buff[256];    
    while( valid ) {
        fprintf( console, "Please enter the message: ");
        fflush( console );
        bzero(buff,256);
        fgets(buff,255,stdin);

        if( 'q' == buff[0] ) {
            valid = 0 ; 
        } else {            
            n = write(sockfd,buff,strlen(buff));
            if ( 0 > n ) {
                valid = 0 ;
                error("ERROR writing to socket");
            } else if ( 0 < n ) {
                bzero(buff,256);
                n = read(sockfd,buff,255);
                if ( 0 > n ) {
                    valid = 0 ; 
                    error("ERROR reading from socket");
                } else if( 0 < n ) {
                    fprintf( console, "%s\n",buff);
                    fflush( console );
                }
            }
        }
    }
    return 0;
}
