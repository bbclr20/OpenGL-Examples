CC=g++
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include -I../Include 
CFLAGS=-g -std=c++11

main.out: main.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

.PHONY: clean
clean:
	rm *.o
	rm *.out
