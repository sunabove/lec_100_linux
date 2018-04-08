#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ; 
    FILE * err = stderr ;
    const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
    fprintf( out, "\nThis is a file open program." );
    fprintf( out, "\n%s", LINE );

    int fd  = -1 ;
    fd = open( "inputFile.txt" , O_RDONLY ) ; 

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open!" );
    } else {
        fprintf( out, "\nSuccess: file open." );
        // close the filedescriptor and may be resued.
        if( -1 == close( fd ) ) {
            int eno = errno ; 
            fflush( out );
            fprintf( err, "\nError: cannot close filedescriptor(%d)", fd ); 
            fprintf( err, "\nstrerror: %s", strerror( eno ) ); 
            fflush( err );
        } else {
            fprintf( out, "\nSuccess: closed the file(%d)" , fd );
        }
    }

    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE );
    // flush the out stream now.
    fflush( out );
    
    return 0;
}
