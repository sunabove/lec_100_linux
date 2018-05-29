/* A simple server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(int sockfd, int clientId ); /* function prototype */

int main(int argc, char **argv) {
    FILE * console = stdout ; 

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

    int clientId = 0;
    struct sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    listen(serverSockFd, 5);
    while (1) {
        clientId ++;
        fprintf( console, "\n[%03d] Acceping a client connection..." , clientId );
        fflush( console );
        int clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if ( 0 > clientSockFd ) {
            perror("ERROR on accept");
	    } if ( 0 <= clientSockFd ) {
            int pid = fork();
            if (pid < 0) {
                // fork error
                perror("ERROR on fork");
            } else if (pid == 0) {
                // child process
                close(serverSockFd);
                dostuff(clientSockFd, clientId); 
            } else {
                // parent process
                close(clientSockFd);
            }
        }
    }
    return 0;
}

/******** DOSTUFF() *********************
 There is a separate instance of this function for each connection.
 It handles all communication once a connnection has been established.
 *****************************************/
void dostuff(int sockfd, int clientId) {
    FILE * console = stdout ;
    int valid = 1 ;
    const int buffLen = 2048;
    char buff[buffLen];

    while( valid ) {
        bzero(buff, buffLen);
        int rn = read(sockfd, buff, buffLen);
        if (rn < 0) {
            valid = 0 ; 
            fprintf(console,"\n[%03d] ERROR reading from socket", clientId);
            fflush( console );
            exit(1);
        } else {
            fprintf( console, "\n[%03d] A client message: %s", clientId, buff);
            fflush( console );
            const int msgLen = 2048;
            char msg [msgLen];
            snprintf ( msg, msgLen, "[%03d] You have sent a message: %s", clientId, buff ); 
            int wn = write(sockfd, msg, strlen( msg ));
            if (wn < 0) {
                valid = 0 ;
                wn = write(sockfd, buff, rn );
                if( wn < 0 ) {
                    valid = 0 ;
                }
            }
        }
    }
    exit( 1 );
}
