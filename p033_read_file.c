#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ; 
    fprintf( out, "This is a file read program.\n" );

    int fd  = -1 ;
    fd = open( "inputFile.txt" , O_RDONLY ) ; 

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        unsigned char c;
        ssize_t nr = 0;
        size_t bufSize = sizeof( c );
        //size_t bufSize = 8;
        fprintf( out, "\nsizeof char = %zu", bufSize);
        fflush( out );
        do {
            nr = read( fd, &c, bufSize ) ;
            if( 0 < nr ) {
                fprintf( out, "\n0x%0X, %d, %c", c, c, c );
            }
        } while( 0 < nr );
        fflush( out );
        // close the filedescriptor and may be resued.
        close( fd );
    }

    fprintf( out, "\nGood bye!\n" );
    fflush( out );
    
    return 0;
}
