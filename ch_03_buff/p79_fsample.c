/* file open */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main( int argc , char ** argv )
{
    FILE * console = stdout ; 

	const char * LINE = "___________________________________________________\n" ; 
    fprintf( console, "%s", LINE );
 	fprintf( console, "\nFile Write Read" );
	fprintf( console, "\n%s", LINE );

	char * fileName = "data.txt" ; 
	
	FILE *in, *out;
	struct pirate {
		char name[100]; /* real name */
		unsigned long booty; /* in pounds sterling */
		unsigned int beard_len; /* in inches */
	} ;
	
	struct pirate p, blackbeard = { "Edward Teach", 950, 48 };
	
	out = fopen ( fileName, "w");
	
	if(!out) {
		perror ("fopen");
		return 1;
	}
	
	if(!fwrite (&blackbeard, sizeof (struct pirate), 1, out)) {
		perror ("fwrite");
		return 1;
	}

	if(fclose (out)) {
		perror ("fclose");
		return 1;
	}

	in = fopen ( fileName, "r");
	
	if(!in) {
		perror ("fopen");
		return 1;
	}

	if(!fread (&p, sizeof (struct pirate), 1, in)) {
		perror ("fread");
		return 1;
	}

	if(fclose (in)) {
		perror ("fclose");
		return 1;
	}
	
	fprintf( console, "\nname=\"%s\" booty=%lu beard_len=%u", p.name, p.booty, p.beard_len);

	fprintf( console, "\n%s", LINE );
    fprintf( console, "\nGood bye!" );
    fprintf( console, "\n%s", LINE ); 
    fflush( console );

	return 0 ;
}
