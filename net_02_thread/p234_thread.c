/* fork example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void * start_thread (void *message) {
   fprintf ( stdout, "\n%s", (const char *) message);
   return message;
}

int main( int argc , char ** argv ){
    FILE * console = stdout ; 

	const char * LINE = "___________________________________________________\n" ; 
    fprintf( console, "%s", LINE );
 	fprintf( console, "\nThread Program" );
	fprintf( console, "\n%s", LINE );

	pthread_t thing1, thing2;
   	const char *message1 = "Thing 1";
   	const char *message2 = "Thing 2";
   	pthread_create (&thing1, NULL, start_thread, (void *) message1);
   	pthread_create (&thing2, NULL, start_thread, (void *) message2);
   	/*  Wait for the threads to exit. */
   	pthread_join (thing1, NULL);
   	pthread_join (thing2, NULL);

	fprintf( console, "\n%s", LINE );
    fprintf( console, "\nGood bye!" );
    fprintf( console, "\n%s", LINE ); 
    fflush( console );

	return 0 ;
}
