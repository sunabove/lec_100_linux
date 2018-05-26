# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#CFLAGS  = -g -Wall
CFLAGS  = 

server: server.c
	$(CC) $(CFLAGS) -o server.out server.c

server-run:
	sudo ./server.out 100

client: client.c
	$(CC) $(CFLAGS) -o client.out client.c

client-run:
	./client.out 127.0.0.1 100

clean:
	$(RM) *.out
