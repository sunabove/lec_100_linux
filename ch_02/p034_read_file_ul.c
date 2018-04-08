#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ; 
    const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
    fprintf( out, "\nLong data read program" );
    fprintf( out, "\n%s", LINE );

    int fd  = -1 ;
    fd = open( "inputFile.txt" , O_RDONLY ) ; 

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        unsigned long word;
        const size_t bufSize = sizeof( word );
        //size_t bufSize = 8;
        fprintf( out, "\nsizeof unsigned long = %zu", bufSize);
        fprintf( out, "\n%s", LINE );
        fflush( out );
        if( SSIZE_MAX < bufSize ) { 
            // check the buffer size
            fprintf( out, "\nbufSize(%zu) is too large." , bufSize );
            fflush( out );
        } else if( SSIZE_MAX >= bufSize ) {
            // when the buffer size less than the max size - 1.
            ssize_t tnr = 0;
            ssize_t nr ; 
            unsigned long * buf = & word ;
            unsigned int idx = 0 ; 
            do {
                idx ++ ;                
                fprintf( out, "\n[%03d] Try to read %zu byte(s) ...." , idx, (bufSize - tnr) ); 
                
                nr = read( fd, buf, bufSize - tnr ) ;
                tnr += nr ; 
                
                fprintf( out, "\n[%03d] %zu byte(s) read.", idx, nr );

                if( 0 == nr ) { // when end of file is encountered.
                    fprintf( out, "\n[%03d] End of file.", idx );
                } else if( bufSize > tnr ) {
                    fprintf( out, "\n[%03d] Bad: Total read number : %zu, Current read number : %zu", idx, tnr, nr );
                    fprintf( out, "\n[%03d] Bad: word = 0x%0lX, %zu", idx, word, word );
                    fprintf( out, "\n[%03d] Bad: Reissuing required.", idx );

                    buf += nr;
                } else if( bufSize == tnr ) {
                    fprintf( out, "\n[%03d] Good: word = 0x%0lX, %zu", idx, word, word );
                    
                    tnr     = 0 ;
                    word    = 0 ;
                    buf     = & word ;
                }

                fprintf( out, "\n%s", LINE );
            } while( 0 < nr );
        }
        fflush( out );
        // close the filedescriptor and may be resued.
        close( fd );
    }

    fprintf( out, "\n%s", LINE );
    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE );
    // flush the out stream now.
    fflush( out );
    
    return 0;
}
