CC=g++ 
LIBS=-lglut -lGLU -lGL -lGLEW
INC=-I../../../Include -I../Include 
CFLAGS=-g -std=c++11
TARGET=HeightMap.out \
       HeightMap.o \
       BasicTessellation.out \
       BasicTessellation.o \
       ViewManager.o

all: $(TARGET)

HeightMap.out: HeightMap.o ViewManager.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

HeightMap.o: HeightMap.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

BasicTessellation.out: BasicTessellation.o ViewManager.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

BasicTessellation.o: BasicTessellation.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

ViewManager.o: ViewManager.cpp
	$(CC) $(CFLAGS) -c  $^ $(INC)

.PHONY: clean
clean:
	rm $(TARGET)
