// num_oper.c
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv){
    printf( "Input a : " ) ;

    double a ;
    scanf( "%lf", &a ) ;

    printf( "Operator(+, -, *, /): " ) ;
    char c[10] ;
    scanf( "%s", c ) ;

    if( strcmp( "+", c ) == 0 ) {
        printf( "You have entered a plus operator.\n" );
    } else {
        printf( "Unknown operator!\n" );
    }

    printf( "Input b : " ) ;

    double b ;
    scanf( "%lf", &b ) ;

    printf( "%g %s %g = %g\n", a, c, b, a*b ) ;

    return 0;
}