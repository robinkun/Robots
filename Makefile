CC  = g++
TARGET  = a.out
SRCS    = getchar.cpp func.cpp node.cpp field.cpp object.cpp gameobj.cpp game.cpp robots.cpp
OBJS    = getchar.o func.o node.o field.o object.o gameobj.o game.o robots.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
