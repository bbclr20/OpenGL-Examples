CC=g++ 
LIBS=-lglut -lGLU -lGL
CFLAGS=-g -ansi -Wall

build: hello_gl.out 

hello_gl.out: main.cpp
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS)

.PHONY: clean
clean:
	rm *.out
