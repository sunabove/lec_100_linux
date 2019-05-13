/* file open */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ; 

	const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
 	fprintf( out, "\nFile Open" );
	fprintf( out, "\n%s", LINE );

	FILE *stream;
	char * fileName = "inputFile.txt" ; 
	stream = fopen ( fileName , "r");
	if (!stream) {
		/* error */
		fprintf( out, "\nError: cannot open file(%s)" , fileName );
	} else {
		fprintf( out, "\nSuccess: open file(%s)" , fileName );

		int idx = 1 ; 
		int c = 1 ;

		while ( EOF != c ) { 
			// read one byte as an int
			c = fgetc(stream);
			if( EOF != c ) {
				fprintf( out, "\nc[%03d] = %c", idx, (char) c);
				idx ++ ; 
			}
		} 
		
		// close file stream
		fclose(stream);
	}

	fprintf( out, "\n%s", LINE );
    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE ); 
    fflush( out );

	return 0 ;
}
