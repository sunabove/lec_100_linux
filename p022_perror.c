#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
    int fd = -1;

    // Always Reset errno before use.
    errno = 0;

    // Make sure you are opening a file that does not exist
    printf( "\nTrying to open a file...." ) ; 

    fd = open("abcd",O_RDONLY);

    if(fd == -1) {
        // Seems like some error occured. Use strerror to print it
        printf( "\nerrono: %d" , errno );
        
        printf("\nstrerror() says -> [%s]\n",(char*)strerror(errno));
        return 1;
    } else {
        printf( "\nSuccess: open the file." );
    }

    return 0;
}