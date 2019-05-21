#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() { 
	pid_t pid;
    int i = 2 ; 
    long int fa = 0 ;
    long int fb = 1 ; 
    long int fc ; 
    fc = fa + fb ; 
    pid = fork();
    if (0 == pid) { 
        printf( "f[%d] = %12ld\n", i, fc);  
        if( i < 50 ) {
            fa = fb ;
            fb = fc ;
            i ++ ;  
        }        
    }   
} 
