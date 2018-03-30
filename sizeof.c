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

    char * str = "ABCDEFGHIJABCDEABCDE" ; 
    size_t strSize = sizeof( str );
    fprintf( out, "\nchar * size of %s : %zu" , str, strSize );

    char strArr[] = "ABCDEFGHIJABCDEABCDE" ;
    size_t strArrSize = sizeof( strArr );
    fprintf( out, "\nchar [] size of %s : %zu" , strArr, strArrSize );

    char *p = str ; 
    size_t pSize = sizeof( p );
    fprintf( out, "\nchar * size of %s : %zu" , "p", pSize );

    int i = 0 ;
    size_t iSize = sizeof( i );
    fprintf( out, "\nsize of %s : %zu" , "i", iSize );

    int * j = & i ; 
    size_t jSize = sizeof( j );
    fprintf( out, "\nsize of %s : %zu" , "j", jSize );

    fprintf( out, "\nGood Bye!" );

    return 0 ;
}
