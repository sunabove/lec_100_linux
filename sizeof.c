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

    wchar_t wc = L'가' ; 
    size_t wcSize = sizeof( wc );
    fprintf( out, "\nwc char size of %c : %zu" , wc, wcSize );

    char * str = "abcdefghi" ; 
    size_t strSize = sizeof( str );
    fprintf( out, "\nchar * size of %s : %zu" , str, strSize );

    char strArr[] = "abcdefghi" ;
    size_t strArrSize = sizeof( strArr );
    fprintf( out, "\nchar [] size of %s : %zu" , strArr, strArrSize );

    fprintf( out, "\nGood Bye!" );

    return 0 ;
}
