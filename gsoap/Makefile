CC = g++
CFLAGS  = -std=c++17 
cflags  = -Wall
LDFLAGS = -lgsoap++ 

%.o: %.cpp $(DEPS)
	$(CC) $< -o $@ -c $(CFLAGS)

client: calcclient.o soapC.o soapcalcProxy.o
	$(CC) -o $@.out $^ $(LDFLAGS) 

server: calcserver.o soapC.o soapcalcService.o
	$(CC) -o $@.out $^ $(LDFLAGS) 	

clean:
	$(RM) *.out *.o
