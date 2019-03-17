/* printf */

#include <stdio.h>

int main( int argc , char ** argv ) {
    FILE * out = stdout ; 

 	fprintf( out, "Program : printf example\n" ); 

	fprintf( out, "%d\n",0) ;
	fprintf( out, "%d\n",-7) ;
	fprintf( out, "%d\n",1560133635) ;
	fprintf( out, "%d\n",-2035065302) ;  

	fprintf( out, "Good bye!\n" );

	return 0 ;
}
