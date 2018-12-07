CC = g++
CFLAGS  = -std=c++17 
cflags  = -Wall
LDFLAGS = -lgsoap++ 

%.o: %.cpp $(DEPS)
	$(CC) $< -o $@ -c $(CFLAGS)

server: calcserver.o soapC.o soapcalcService.o
	$(CC) -o $@.out $^ $(LDFLAGS) 

clean:
	$(RM) *.out *.o
