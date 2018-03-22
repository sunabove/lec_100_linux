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

    char * str = "abcdefghi" ; 
    size_t strSize = sizeof( str );
    fprintf( out, "\nchar * size of %s : %zu" , str, strSize );

    char strArr[] = "abcdefghi" ;
    size_t strArrSize = sizeof( strArr );
    fprintf( out, "\nchar [] size of %s : %zu" , strArr, strArrSize );

    fprintf( out, "\nGood Bye!" );

    return 0 ;
}
