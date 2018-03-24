#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    FILE * out = stdout ; 
    fprintf( out, "Hello!\nThis is perror() program v1.0." );

    int fd = -1;

    // Always Reset errno before use.
    errno = 0;

    // Make sure you are opening a file that does not exist
    fprintf( out, "\nTrying to open a file...." ) ; 

    fd = open("abcd",O_RDONLY);

    if(-1 == fd) {
        // Seems like some error occured. Use strerror to print it
        printf( "\nerrono: %d" , errno );

        perror ( "open failed." );
        
        printf("\nstrerror() : %s",(char*)strerror(errno));
    } else {
        perror( "\nSuccess: open the file." );
        if (close (fd) == -1 ) {
            perror ( "close failed" );
        }
    }

    printf( "\nGood bye!" ); 

    return 0;
}
