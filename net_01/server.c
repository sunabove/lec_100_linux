/* A simple server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dostuff(const int sockfd, const int clientId ); /* function prototype */

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

    struct sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int clientId = 0;

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
            if (pid < 0) { // fork error
                perror("ERROR on fork");
            } else if (pid == 0) { // child process
                close(serverSockFd);
                dostuff(clientSockFd, clientId); 
            } else { // parent process
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
void dostuff(const int sockfd, const int clientId) {
    FILE * console = stdout ;
    int valid = 1 ;
    char readMsg[2048];

    while( valid ) {
        bzero(readMsg, sizeof(readMsg));

        // read a line
        int rn = 0 ;
        char * buf = readMsg;
        do {
            buf += rn ;
            rn = read(sockfd, buf, 1);
        } while( -1 < rn && '\n' != *buf );
        // -- read a line

        if ( 0 > rn ) {
            valid = 0 ; 
            fprintf(console,"\n[%03d] ERROR: reading from socket", clientId);
            fflush( console );
            exit(1);
        } else if( -1 < rn ) {
            fprintf( console, "\n[%03d] a client message: %s", clientId, readMsg);
            fflush( console );
            char sendMsg [2048];
            snprintf ( sendMsg, sizeof(sendMsg), "[%03d] You have sent a message: %s", clientId, readMsg ); 
            int wn = write(sockfd, sendMsg, strlen( sendMsg ));
            if (wn < 0) {
                valid = 0 ;
            }
        }
    }
    exit( 1 );
}
// -- dostuff
// --