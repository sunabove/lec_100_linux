#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <vector>
#include <string>

#include "Message.h" 

class ChatRoom ;

class Socket  {
    public: 

    int valid ; 
    int sockfd;
    unsigned int clientId ;
    const char * appName ;  
    FILE * console ;

    ChatRoom * chatRoom ;

    public: Socket() { 
        this->valid = true ; 
        this->console = stdout ; 
    }

    // read a client message
    public: Message readMessage( ) {
        Message message ;
        int valid = message.readMessage( this->sockfd );

        message.clientId = clientId ;  

        this->valid = valid ; 

        return message;
    }

    // write a message
    public: void writeMessage( Message * message ) {
        
        std::string textOrg = message->text ;

        if( message->clientId == this->clientId ) {
            message->text = "*" + message->text ; 
        } 

        int valid = message->writeMessage( this->sockfd );

        message->text = textOrg;

        this->valid = valid ; 
    } 

} ;

// --