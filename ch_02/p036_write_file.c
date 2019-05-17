#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ;
    const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
    fprintf( out, "\nA file write program." );
    fprintf( out, "\n%s", LINE );

    int fd  = -1 ;
    const char * fileName = "outputFile.txt" ; 
    //fd = creat( fileName, 0644 ) ; 
    fd = open (fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        unsigned char c;
        
        fflush( out );

        ssize_t nr = 0 ;        
        for( char c = 'A' ; -1 < nr && c <= 'Z' ; c ++ ) {  
            /* write the string in 'buf' to 'fd' */
            nr = write(fd, &c, sizeof( c )); 
        }

        // close the filedescriptor and may be resued.
        close( fd );
    }

    fprintf( out, "\n%s", LINE );
    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE );
    fflush( out );
    
    return 0;
}
