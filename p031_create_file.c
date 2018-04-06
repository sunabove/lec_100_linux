#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char ** argv) {
    FILE * out = stdout ; 
    fprintf( out, "This is a file creat program.\n" );

    int fd  = -1 ;
    const char * fileName = "outputFile.txt" ; 
    fd = creat( fileName, 0644 ) ; 
    //fd = open (fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot create a file [%s]!" , fileName );
    } else if( -1 < fd ) {
        fprintf( out, "\nSuccess: create a file [%s]." , fileName ); 
        close( fd );
    }

    fprintf( out, "\nGood bye!\n" );
    fflush( out );
    
    return 0;
}
