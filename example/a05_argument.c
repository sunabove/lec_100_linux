/* c main funtions / argc, argv */

#include <stdio.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ; 

	const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
 	fprintf( out, "\nArgument Print Program" );
	fprintf( out, "\n%s", LINE );

	for( int i = 0, iLen = argc ; i < iLen ; i ++ ) {
		fprintf( out, "\nargv[%d] = %s" , i, argv[i] );
	}

	fprintf( out, "\n%s", LINE );
    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE ); 
    fflush( out );

	return 0 ;
}
