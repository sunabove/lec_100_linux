/* SizeOf C program: */

#include <stdio.h>
#include <wchar.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ; 

 	fprintf( out, "Hello World!" );

    char c = 'A' ; 

    size_t cSize = sizeof( c );  

    fprintf( out, "\nchar size of %c : %zu", c, cSize ); 

    wchar_t ga = L'가' ; 

    size_t gaSize = sizeof( ga );

    fprintf( out, "\nga char size of %c : %zu" , ga, gaSize );

 	fprintf( out, "\nGood Bye!" );

	return 0 ;
}