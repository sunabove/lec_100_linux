CC = g++
cc = gcc
CFLAGS  = -Wall
LDFLAGS = -lpthread -ldl -lzf_log

%.o: %.c $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(cc) $< -c -o $@ $(CFLAGS)

%.o: %.cpp $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(CC) $< -c -o $@ $(CFLAGS)

all: main.o hello.o factorial.o
	@echo "======================================="
	@echo "Linking $<" 
	$(CC) -o $@.out $^ $(LDFLAGS) 

clean:
	$(RM) *.o *.out
