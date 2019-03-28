CC=g++
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include -I../Include 
CFLAGS=-g -std=c++11
TARGETS=SimpleExample.out \
        BlendingExample.out \
		GrayScaleCube.out \
        ViewManager.o \
		GrayScaleCube.o \
		ImageProcessing.out

all: $(TARGETS)

SimpleExample.out: SimpleExample.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

BlendingExample.out: BlendingExample.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

ImageProcessing.out: ImageProcessing.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

ViewManager.o: ViewManager.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

GrayScaleCube.o: GrayScaleCube.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

GrayScaleCube.out: GrayScaleCube.cpp ViewManager.o
	$(CC) $(CFLAGS) -o $@ $^ $(INC) $(LIBS)

.PHONY: clean
clean:
	rm $(TARGETS)

