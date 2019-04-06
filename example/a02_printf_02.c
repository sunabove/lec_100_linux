/* printf */

#include <stdio.h>

int main( int argc , char ** argv ) {
    FILE * out = stdout ; 

 	fprintf( out, "Program : printf example\n" ); 

	// integer
	fprintf( out, "Integer example\n" );
	fprintf( out, "%d\n", 0);
	fprintf( out, "%d\n", -7);
	fprintf( out, "%d\n", 1560133635);
	fprintf( out, "%d\n\n", -2035065302);

	// width option
	fprintf( out, "Width option\n" );
	fprintf( out, "%5d\n",0);
	fprintf( out, "%5d\n",-7);
	fprintf( out, "%5d\n",1560133635) ;
	fprintf( out, "%5d\n\n",-2035065302) ;

	// justify option
	fprintf( out, "Width option\n" );
	fprintf( out, "%-5d\n",0) ;
	fprintf( out, "%-5d\n",-7) ;
	fprintf( out, "%-5d\n",1560133635) ;
	fprintf( out, "%-5d\n\n",-2035065302) ;

	// zero-fill option
	fprintf( out, "Zero fill option\n" );
	fprintf( out, "%05d\n",0) ;
	fprintf( out, "%05d\n",-7) ;
	fprintf( out, "%05d\n",1560133635) ;
	fprintf( out, "%05d\n\n",-2035065302);

	// plus signs option
	fprintf( out, "Plus signs\n" );
	fprintf( out, "%+5d\n",0) ;
	fprintf( out, "%+5d\n",-7) ;
	fprintf( out, "%+5d\n",1560133635) ;
	fprintf( out, "%+5d\n\n",-2035065302) ;

	// invisible plus sign
	fprintf( out, "Invisible plus signs\n" );
	fprintf( out, "%+-5d\n",0) ;
	fprintf( out, "%+-5d\n",-7) ;
	fprintf( out, "%+-5d\n",1560133635) ;
	fprintf( out, "%+-5d\n",-2035065302);
	fprintf( out, "% -5d\n",0) ;
	fprintf( out, "% -5d\n",-7) ;
	fprintf( out, "% -5d\n",1560133635) ;
	fprintf( out, "% -5d\n",-2035065302);
	fprintf( out, "%-5d\n", 0) ;
	fprintf( out, "%-5d\n",-7) ;
	fprintf( out, "%-5d\n",1560133635) ;
	fprintf( out, "%-5d\n\n",-2035065302) ;

	// plus, space and zero
	fprintf( out, "Plus, space and zero\n" );
	fprintf( out, "% 05d\n",0)          ;
	fprintf( out, "% 05d\n",-7)         ;
	fprintf( out, "% 05d\n",1560133635) ;
	fprintf( out, "% 05d\n",-2035065302);
	fprintf( out, "%+05d\n",0)          ;
	fprintf( out, "%+05d\n",-7)         ;
	fprintf( out, "%+05d\n",1560133635) ;
	fprintf( out, "%+05d\n\n",-2035065302);

	// Strings
	fprintf( out, "Strings\n" );
	fprintf( out, "%5s\n","") ;
	fprintf( out, "%5s\n","a") ;
	fprintf( out, "%5s\n","ab") ;
	fprintf( out, "%5s\n","abcdefg") ;
	fprintf( out, "%-5s\n","") ;
	fprintf( out, "%-5s\n","a") ;
	fprintf( out, "%-5s\n","ab") ;
	fprintf( out, "%-5s\n\n","abcdefg") ;

	// Floating point
	float e = 2.718281828 ; 
	fprintf( out, "Floating point\n" );
	fprintf( out, "%.0f\n",e)   ;
	fprintf( out, "%.0f.\n",e)  ;
	fprintf( out, "%.1f\n",e)   ;
	fprintf( out, "%.2f\n",e)   ;
	fprintf( out, "%.6f\n",e)   ;
	fprintf( out, "%f\n",e)     ;
	fprintf( out, "%.7f\n",e)   ;
	fprintf( out, "%5.0f\n",e)  ;
	fprintf( out, "%5.0f.\n",e) ;
	fprintf( out, "%5.1f\n",e)  ;
	fprintf( out, "%5.2f\n",e)  ;
	fprintf( out, "%5.7f\n",e)  ; 

	fprintf( out, "%5.1f\n",e)   ;
	fprintf( out, "%-5.1f\n",e)  ;
	fprintf( out, "%+5.1f\n",e)  ;
	fprintf( out, "%+-5.1f\n",e) ;
	fprintf( out, "%05.1f\n",e)  ;
	fprintf( out, "%+05.1f\n",e) ;
	fprintf( out, "% 05.1f\n",e) ;
	fprintf( out, "%- 5.1f\n\n",e) ;

	fprintf( out, "Good bye!\n" );

	return 0 ;
}
