#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ; 
    fprintf( out, "A file reading program." );

    int fd  = -1 ;
    fd = open( "inputFile.txt" , O_RDONLY ) ; 

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        unsigned char c;
        ssize_t ret = 0;
        size_t len = sizeof( c );
        fprintf( out, "\nsizeof char = %zu", len);
        fflush( out );
        void * buf = & c ; 
        while( len > 0 && ( ret = read( fd, buf, len ) ) > 0 ) {
            fprintf( out, "\n0x%0X, %d, %c", c, c, c );
        } ;
        fflush( out );
        // close the filedescriptor and may be resued.
        close( fd );
    }

    fprintf( out, "\nGood bye!\n" );
    fflush( out );
    
    return 0;
}
