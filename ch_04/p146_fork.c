#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() { 
	pid_t pid;
    int i = 0 ; 
    pid = fork();
    if (pid > 0) {
        i ++ ; 
        printf( "parent process i = %d\n", i); 
    } else if (0 == pid) {
        printf( "child process i = %d\n", i); 
    } else if (pid == -1) {
        perror ("fork error ");
    }    
} 
