#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
    printf( "Hello!\nThis is perror() program v1.0." );

    int fd = -1;

    // Always Reset errno before use.
    errno = 0;

    // Make sure you are opening a file that does not exist
    printf( "\nTrying to open a file...." ) ; 

    fd = open("abcd",O_RDONLY);

    if(fd == -1) {
        // Seems like some error occured. Use strerror to print it
        printf( "\nerrono: %d" , errno );
        
        printf("\nstrerror() : %s",(char*)strerror(errno));
    } else {
        printf( "\nSuccess: open the file." );
    }

    printf( "\nGood bye!" ); 

    return 0;
}