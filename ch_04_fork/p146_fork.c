#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() { 
    pid_t pid;
    int i = 1 ;
    pid = fork(); // process count 2
    if( pid > 0 ) {
        i += 1 ; 
        printf( "parent process i = %d\n", i); 
    } else if (0 == pid) {
        i += 2 ;
        printf( "child process i = %d\n", i); 
    } else if (pid == -1) {
        perror ("fork error ");
    }
} 
