#include <stdio.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <locale.h>

int main(void) {
    setlocale( LC_ALL, "" ) ;

    int fd = -1;

    // Always Reset errno before use.
    errno = 0;

    // Make sure you are opening a file that does not exist
    wprintf( L"\nTrying to open a file...." ) ; 

    fd = open("abcd",O_RDONLY);

    if(fd == -1) {
        // Seems like some error occured. Use strerror to print it
        wprintf( L"\nerrono: %d" , errno );
        
        wprintf( L"\nStrerror() says -> [%s]\n",(char*)strerror(errno));
        return 1;
    } else {
        wprintf( L"\nSuccess: open the file." );
    }

    return 0;
}