# Variables
CC = g++
CFLAGS = -g -Wall
TARGET = trigonometry
OBJS = main.o MyTrigFunction.o

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

MyTrigFunction.o: MyTrigFunction.cpp MyTrigFunction.h
	$(CC) $(CFLAGS) -c MyTrigFunction.cpp

clean:
	rm -rf -v *.o $(TARGET)
