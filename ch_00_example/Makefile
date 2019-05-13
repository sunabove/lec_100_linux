# the compiler: gcc for C program, define as g++ for C++
#CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# the build target executable:
TARGET = a03_sizeof

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o a.out $(TARGET).c

clean:
	$(RM) $(TARGET) a.out
