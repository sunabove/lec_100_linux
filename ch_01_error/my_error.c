#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    printf( "Hello...\n" );
    
    const char * buf = "AB1234" ;
    printf( "%s\n", buf ); 
     
    unsigned long ul ;  
    errno = 0;
    ul = strtoul(buf, NULL, 0);
    
    if(errno){
        perror ("strtoul");
    } else {
        printf( "ul = %zd\n", ul );
        printf( "Success\n" );
    }

    return 0;
}
