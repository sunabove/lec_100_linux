CC = g++
cc = gcc
CFLAGS  = -Wall
LDFLAGS = -lpthread -ldl

%.o: %.c $(DEPS)
	$(cc) $< -c -o $@ $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) $< -c -o $@ $(CFLAGS)

my_sqlite: my_sqlite.o sqlite3.o 
	$(CC) -o $@.out $^ $(LDFLAGS) 

clean:
	$(RM) *.o *.out
