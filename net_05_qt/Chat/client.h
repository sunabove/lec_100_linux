#pragma once

#include <stdio.h>

#include "Socket.h"

class Client {
public:
    bool connected ;
    Socket clientSocket ;
public:
    Client() {
        this->connected = false ;
    }

public: void connectServer(const char * hostname, int portno ) {
        if( this->connected ) {
            return ;
        }

        FILE * console = stdout ;
        struct hostent *server = gethostbyname(hostname);

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
            this->connected = false ;
        } else {
            this->connected = true ;
            Socket * clientSocket = & this->clientSocket ;
            clientSocket->sockfd     = sockfd;
            clientSocket->valid      = 1 ;
            clientSocket->console    = console ;
        }
    }

};
