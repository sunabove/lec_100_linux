#CC = g++
CC = gcc
CFLAGS  = -Wall
LDFLAGS = -lpthread -ldl

%.o: %.cpp $(DEPS)
	$(CC) $< -c -o $@ $(CFLAGS)

sqlite: shell.o sqlite3.o 
	$(CC) -o $@ $^ $(LDFLAGS) 

clean:
	$(RM) sqlite *.o
