CC=g++ 
LIBS=-lglut -lGLU -lGL
CFLAGS=-g -ansi -Wall

main.out: main.o Common.o tiny_obj_loader.o ViewManager.o
	$(CC) $(CFLAGS) -o  $@ $^ $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c  $^

Common.o: Common.cpp
	$(CC) $(CFLAGS) -c  $^

tiny_obj_loader.o: tiny_obj_loader.cpp
	$(CC) $(CFLAGS) -c  $^

ViewManager.o: ViewManager.cpp
	$(CC) $(CFLAGS) -c  $^

.PHONY: clean
clean:
	rm *.o
	rm *.out
