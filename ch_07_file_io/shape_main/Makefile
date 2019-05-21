CC = g++
cc = gcc
CFLAGS  = -std=c++17 -Wall
cflags  = -Wall
LDFLAGS = -lpthread -ldl

%.o: %.c $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(cc) $< -c -o $@ $(cflags)

%.o: %.cpp $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(CC) $< -c -o $@ $(CFLAGS)

a: ShapeReaderApp.o Shape.o zf_log.o
	@echo "======================================="
	@echo "Linking $<" 
	$(CC) -o $@.out $^ $(LDFLAGS) 

clean:
	$(RM) *.o *.out
