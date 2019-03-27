CC=g++
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include -I../Include 
CFLAGS=-g -std=c++11

all: SimpleExample.out BlendingExample.out

SimpleExample.out: SimpleExample.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

BlendingExample.out: BlendingExample.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

.PHONY: clean
clean:
	rm *.o
	rm *.out
