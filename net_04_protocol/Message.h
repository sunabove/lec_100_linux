#pragma once

#include <string>

class Message {
    public:
        int clientId ;
        std::string text ; 
        bool valid ;
    
    public: 
        Message() {
            this->valid = true;
        }

        Message(const Message & message ) {
            this->clientId = message.clientId ;
            this->text = message.text ;
            this->valid = message.valid ; 
        }
} ; 