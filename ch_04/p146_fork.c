#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() { 
	pid_t pid;
    int i = 0 ; 
    pid = fork ();
    if (pid > 0) {
        i ++ ; 
        printf ("I am the parent of pid=%d!\n", pid);
        printf( "parent i = %d\n", i); 
    } else if (! pid) {
        printf ("I am the child!\n");
        printf( "child i = %d\n", i); 
    } else if (pid == -1) {
        perror ("fork error ");
    }    
} 
