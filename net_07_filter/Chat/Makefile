CC = g++
#CFLAGS  = -Wall
CFLAGS  = -std=c++17 -Wall
cflags  = -Wall
LDFLAGS = -pthread 

%.o: %.cpp $(DEPS)
	$(CC) $< -o $@ -c $(CFLAGS)

server: OpCode.o OpCodeAck.o OpCodeNack.o OpCodeFile.o OpCodeMsg.o OpCodeExit.o OpCodeSysInfo.o ChatRoom.o Socket.o Server.o zf_log.o 
	$(CC) -o $@.out $^ $(LDFLAGS)

server-run:
	sudo ./server.out 100

clean:
	$(RM) *.out *.o
