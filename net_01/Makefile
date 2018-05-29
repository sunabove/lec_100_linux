#CFLAGS  = -g -Wall
CC = gcc
CFLAGS  = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: server.o
	$(CC) -o $@.out $^ $(CFLAGS)

server-run:
	sudo ./server.out 100

client: client.o
	$(CC) -o $@.out $^ $(CFLAGS)

client-run:
	./client.out 127.0.0.1 100

clean:
	$(RM) *.out
