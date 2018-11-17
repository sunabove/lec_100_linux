CC = g++
cc = gcc
CFLAGS  = -Wall
LDFLAGS = -lpthread -ldl

%.o: %.c $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(cc) $< -c -o $@ $(CFLAGS)

%.o: %.cpp $(DEPS)
	@echo "======================================="
	@echo "Compiling $<"
	$(CC) $< -c -o $@ $(CFLAGS)

a: ShapeReader.o Shape.o zf_log.o
	@echo "======================================="
	@echo "Linking $<" 
	$(CC) -o $@.out $^ $(LDFLAGS) 

clean:
	$(RM) *.o *.out
