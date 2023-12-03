CC=g++
CFLAGS= -c -Wall -g
HEADERS= schematic.h
SOURCES= main.cpp schematic.cpp part.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aoc

all: $(SOURCES) $(EXECUTABLE) clean
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o $(OBJECTS)