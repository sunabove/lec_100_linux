#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main( int argc, char ** argv) {

    printf( "################\n" );
    printf( "This is a file open program.\n" );

    int fd ;

    fd = open( "/home/sunabove/bbb.txt" , O_RDONLY ) ; 

    if( fd == -1 ) {
        printf( "Cannot open!\n" );
    } else {
        printf( "Success: file open.\n" );
    }

    printf( "Good bye!\n" );
    printf( "################\n" );
    
    return 0;

}
