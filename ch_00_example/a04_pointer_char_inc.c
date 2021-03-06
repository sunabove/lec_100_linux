/* SizeOf C program: */

#include <stdio.h>
#include <wchar.h>

int main( int argc , char ** argv )
{
    FILE * out = stdout ;
    const char * LINE = "___________________________________________________\n" ; 
    fprintf( out, "%s", LINE );
    fprintf( out, "\nChar pointer increase test." );
    fprintf( out, "\n%s", LINE );

    char s[20] = "ABCDEFGHIJ";

    char * p = s; 

    unsigned long addr, addrPrev = 0  ; 
    for( int i = 0 , iLen = sizeof( s ); i < iLen ; i ++ ) {
        // get the memory address by type casting.
        unsigned long addr = (unsigned long)( p ) ; 
        unsigned long addrInc = addrPrev < 1 ? 0 : addr - addrPrev ; 
        fprintf( out, "\n[%03d] address : 0x%0lX = %zu, inc = %zu, value = %c" ,
                            i+1, addr, addr, addrInc , *p );
        // increase the pointer by increment opeator.
        addrPrev = addr ; 
        p ++ ; 
    }

    fprintf( out, "\n%s", LINE );
    fprintf( out, "\nGood bye!" );
    fprintf( out, "\n%s", LINE );
    // flush the out stream now.
    fflush( out );

    fflush( out );

    return 0 ;
}
