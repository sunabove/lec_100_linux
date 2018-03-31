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
        fprintf( out, "\nCannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        unsigned long word;
        ssize_t nr = 0;
        size_t bufSize = sizeof( word );
        //size_t bufSize = 8;
        fprintf( out, "\nsizeof unsigned long = %zu", bufSize);
        fflush( out );
        if( 100 < bufSize ) {
            fprintf( out, "\nbufSize(%zu) is too large." , bufSize );
            fflush( out );
        } else if( 100 > bufSize ) {
            do {
                nr = read( fd, &word, bufSize ) ;
                if( 0 < nr ) {
                    fprintf( out, "\n%0lX , %zu", word , word );
                }
            } while( 0 < nr );
        }
        fflush( out );
        // close the filedescriptor and may be resued.
        close( fd );
    }

    fprintf( out, "\nGood bye!" );
    fflush( out );
    
    return 0;
}
