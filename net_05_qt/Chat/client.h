#pragma once

#include <stdio.h>

#include "Socket.h"

void * readMessageThread( void * args );  
void * writeMessageThread( Socket * socket );  

int clientMain(char * hostname , int portno ) ;