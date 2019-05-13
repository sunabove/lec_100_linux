/* printf */

#include <stdio.h>

int main( int argc , char ** argv ) {
    FILE * out = stdout ; 

 	fprintf( out, "Hello World!\n" );
	fprintf( out, "printf format specifier example program.\n" );

	fprintf( out, "\e[1mbold\e[0m\n" );
	fprintf( out, "\e[4munderline\e[0m\n" );
	fprintf( out, "\e[31mHello World\e[0m\n" ); 
	fprintf( out, "\e[9mstrikethrough\e[0m\n" );
	fprintf( out, "\e[3mitalic\e[0m\n" );	

	fprintf( out, "\nGood bye!\n" );

	return 0 ;
}
