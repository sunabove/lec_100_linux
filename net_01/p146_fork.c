/* fork example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc , char ** argv ){
    FILE * console = stdout ; 

	const char * LINE = "___________________________________________________\n" ; 
    fprintf( console, "%s", LINE );
 	fprintf( console, "\nFork Program" );
	fprintf( console, "\n%s", LINE );

	pid_t pid;
	pid = fork();
	int x = 1 ;
	if ( 0 < pid ) {
		fprintf( console, "\nI am the parent of pid = %d!", pid);
		x ++ ; 
		fprintf( console, "\nParent x = %d", x);
	} else if ( 0 == pid) {
		fprintf( console, "\nI am the child!");
		x-- ;
		fprintf( console, "\nChild x = %d", x);
	} else if ( -1 == pid ) {
		perror ("fork");
	}

	fprintf( console, "\n%s", LINE );
    fprintf( console, "\nGood bye!" );
    fprintf( console, "\n%s", LINE ); 
    fflush( console );

	return 0 ;
}
