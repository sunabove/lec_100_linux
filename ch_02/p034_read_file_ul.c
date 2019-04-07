#include <errno.h>
#include <string.h>
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
    const char * inputFileName = "inputFile.txt" ; 
    fd = open( inputFileName , O_RDONLY ) ;
    //fd = STDIN_FILENO ;  

    if( -1 == fd ) {
        fprintf( out, "\nError: cannot open(%d) : %s", fd, inputFileName );
    } else if( -1 < fd ) {
        fprintf( out, "\nSuccess: file open(%d) : %s" , fd, inputFileName );
        unsigned long word;
        const size_t bufSize = sizeof( word );
        fprintf( out, "\nsizeof unsigned long = %zu", bufSize);
        fprintf( out, "\n%s", LINE );
        fflush( out );
        
        unsigned int idx = 0 ; 
        
        ssize_t ret = 1 ; 
        while( ret > 0 ) {  
            word = 0 ; 
            ssize_t len = bufSize ; 
            void * buf = & word ;  
            
            while( len > 0 && ret > 0 ) {
                idx ++ ;                
                fprintf( out, "\n[%03d] Try to read %zu byte(s) ...." , idx, ( len ) ); 
                fflush( out );
                // set errno as 0 before to check
                errno = 0 ; 
                // try to rea len bytes from fd to buf
                ret = read( fd, buf, len ) ;
                // store the errno on the local variable
                const int err = errno ; 
                fprintf( out, "\n[%03d] %zu byte(s) read.", idx, ret );

                if( -1 == ret ) {
                    if( EINTR == err ) {
                        // a signal was received, continue to read
                        ret = 1; 
                    } else {
                        fprintf(stderr, "\nError while reading : %s", strerror(err) );
                    }
                } else if( 0 == ret ) {
                    // when end of file is encountered.
                    fprintf( out, "\n[%03d] End of file.", idx );
                } else {
                    len -= ret;
                    buf += ret; 

                    if( 0 < len ) {
                        fprintf( out, "\n[%03d] Bad: Total read number : %zu, Current read number : %zu", idx, (bufSize - len), len );
                        fprintf( out, "\n[%03d] Bad: word = 0x%0lX, %zu", idx, word, word );
                        fprintf( out, "\n[%03d] Bad: Reissuing required.", idx ); 
                    } else if( 0 == len ) {
                        fprintf( out, "\n[%03d] Good: word = 0x%0lX, %zu", idx, word, word ); 
                    }
                }
            } 

            fprintf( out, "\n%s", LINE );
        } ;

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
