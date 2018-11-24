CC = g++
CFLAGS  = -Wall
#CFLAGS  = -std=c++17 -Wall
cflags  = -Wall
LDFLAGS = -pthread 

%.o: %.cpp $(DEPS)
	$(CC) $< -c -o $@ $(CFLAGS)

server: OpCode.o OpCodeMsg.o ChatRoom.o Socket.o Server.o zf_log.o 
	$(CC) -o $@.out $^ $(LDFLAGS)

server-run:
	sudo ./server.out 100

clean:
	$(RM) *.out *.o
