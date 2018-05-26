/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int); /* function prototype */

int logOut( const char * msg ) {
    FILE * console = stdout;
    fprintf( console, "%s", msg );
    fflush( console );
    return 1;
} 

void error(char *msg) {
    perror(msg); 
}

int main(int argc, char *argv[])
{
    FILE * console = stdout ; 
    int sockfd, newsockfd, portno, clilen, pid;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    while (1)
    {
        logOut( "\nAcceping a client connection..." );
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            error("ERROR on accept");
	    }
        pid = fork();
        if (pid < 0) {
            error("ERROR on fork");
        } else if (pid == 0) {
            // child process
            close(sockfd);
            dostuff(newsockfd); 
        } else {
            // parent process
            close(newsockfd);
        }
    }
    /* end of while */
    return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
void dostuff(int sock)
{
    int valid = 1 ;
    int rn;
    char buff[256];

    while( valid ) {
        bzero(buff, 256);
        rn = read(sock, buff, 255);
        if (rn < 0) {
            valid = 0 ; 
            error("ERROR reading from socket");
            exit(1);
        } else {
            printf("\nA client message: %s\n", buff);
            char msg [1024];
            snprintf ( msg, 1024, "You have sent a message: %s", buff ); 
            int wn = write(sock, msg, strlen( msg ));
            if (wn < 0) {
                valid = 0 ;
                wn = write(sock, buff, rn );
                if( wn < 0 ) {
                    valid = 0 ;
                }
            }
        }
    }
    exit( 1 );
}
