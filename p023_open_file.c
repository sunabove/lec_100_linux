#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char ** argv) {

    printf( "################\n" );
    printf( "This is a file open program.\n" );

    int fd  = -1 ;
    fd = open( "test.txt" , O_RDONLY ) ; 

    if( -1 == fd ) {
        printf( "Cannot open!\n" );
    } else {
        printf( "Success: file open.\n" );
        // close the filedescriptor and may be resued.
        close( fd );
    }

    printf( "Good bye!\n" );
    printf( "################\n" );
    
    return 0;

}
