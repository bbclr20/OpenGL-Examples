CC=g++ 
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include
CFLAGS=-std=c++11 -g

buildAll: vertixBasic.out shader.out

vertixBasic.out: vertixBasic.cpp 
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

shader.out: shader.cpp 
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

.PHONY: clean
clean:
	rm *.out
