CC=g++ 
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include
CFLAGS=-g -ansi -Wall

buildAll: mouseEvent.out  teapotRender.out  transform.out  windowCreate.out

mouseEvent.out: mouseEvent.cpp
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

teapotRender.out: teapotRender.cpp
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

transform.out: transform.cpp
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

windowCreate.out: windowCreate.cpp
	$(CC) $(CFLAGS) $^ -o  $@ $(LIBS) $(INC)

.PHONY: clean
clean:
	rm *.out
