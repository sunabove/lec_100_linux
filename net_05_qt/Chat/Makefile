CC = g++
CFLAGS  = -g -Wall
LDFLAGS = -pthread 

%.o: %.cpp $(DEPS)
	$(CC) $< -c -o $@ $(CFLAGS)

server: server.o
	$(CC) -o $@.out $^ $(LDFLAGS)

server-run:
	sudo ./server.out 100 

clean:
	$(RM) *.out *.o
