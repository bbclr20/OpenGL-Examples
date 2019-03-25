CC=g++ 
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include
CFLAGS=-g -std=c++11

main.out: main.o ViewManager.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

ViewManager.o: ViewManager.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

.PHONY: clean
clean:
	rm *.o
	rm *.out
