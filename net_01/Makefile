# the compiler: gcc for C program, define as g++ for C++
#CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = server

all: $(TARGET)

server: server.c
	$(CC) $(CFLAGS) -o server.out server.c

client: client.c
	$(CC) $(CFLAGS) -o client.out client.c

clean:
	$(RM) *.out
