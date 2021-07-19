CC=g++
CFLAGS= -std=c++0x -c -Wall
LDFLAGS=-std=c++0x -g

SOURCES=main.cpp Critter.cpp Ant.cpp Gameboard.cpp Point.cpp Doodlebug.cpp Menu.cpp Interface.cpp
HEADERS= Critter.hpp Ant.hpp Gameboard.hpp Point.hpp Doodlebug.hpp Menu.hpp Interface.hpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=group10

all: $(SOURCES) $(HEADERS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $(EXECUTABLE)

%.o:%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
