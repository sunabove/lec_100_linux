/* argument value print program */

#include <stdio.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ; 

	fprintf( out, "argc = %d\n", argc );

	for( int i = 0, iLen = argc ; i < iLen ; i ++ ) {
		fprintf( out, "argv[%d] = %s\n" , i, argv[i] );
	}

	return 0 ;
}
