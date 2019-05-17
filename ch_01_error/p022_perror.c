#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    FILE * out = stdout ; 
    fprintf( out, "Hello!\nThis is perror() program v1.1." );

    int fd = -1;

    // Always Reset errno before use.
    errno = 0;

    // Make sure you are opening a file that does not exist
    fprintf( out, "\nTrying to open a file...." ) ; 

    fd = open("abcd",O_RDONLY);

    if( -1 == fd ) {
        // Seems like some error occured. Use strerror to print it
        fprintf( out, "\nerrono: %d" , errno );
        fflush( out );
        perror ( "\nopen failed." );
        fflush( out );
        fprintf( out, "\nstrerror() : %s", strerror(errno) );
    } else {
        fflush( out );
        perror( "\nSuccess: open the file." );
        fflush( out );
        if (close (fd) == -1 ) {
            perror ( "\nclose failed" );
        }
    }

    fprintf( out, "\nGood bye!" ); 
    fflush( out );

    return 0;
}
