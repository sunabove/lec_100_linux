/* SizeOf C program: */

#include <stdio.h>
#include <wchar.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ;
    fprintf( out, "Hello World!" );

    char c = 'A' ; 
    size_t cSize = sizeof( c );  
    fprintf( out, "\nsize of %s : %zu", "char", cSize ); 

    wchar_t wc = L'가' ; 
    size_t wcSize = sizeof( wc );
    fprintf( out, "\nsize of %s : %zu" , "wchar_t", wcSize );

    char * str = "ABCDEFGHIJABCDEABCDE" ; 
    size_t strSize = sizeof( str );
    fprintf( out, "\nsize of %s : %zu" , "char *", strSize );

    char strArr[] = "ABCDEFGHIJABCDEABCDE" ;
    size_t strArrSize = sizeof( strArr );
    fprintf( out, "\nsize of %s : %zu" , "char []", strArrSize );

    char *p = str ; 
    size_t pSize = sizeof( p );
    fprintf( out, "\nsize of %s : %zu" , "char *", pSize );

    int i = 0 ;
    size_t iSize = sizeof( i );
    fprintf( out, "\nsize of %s : %zu" , "int", iSize );

    int * j = & i ; 
    size_t jSize = sizeof( j );
    fprintf( out, "\nsize of %s : %zu" , "int *", jSize );
    
    fprintf( out, "\nsize of %s : %zu" , "long", sizeof( long ) );

    fprintf( out, "\nsize of %s : %zu" , "unsigned long", sizeof( unsigned long ) );
    
    fprintf( out, "\nGood Bye!" );

    fflush( out );

    return 0 ;
}
