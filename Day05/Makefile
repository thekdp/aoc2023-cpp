CC=g++
CFLAGS= -c -Wall -std=c++20
HEADERS=
SOURCES= main.cpp almanac.cpp converter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aoc

all: $(SOURCES) $(EXECUTABLE) clean
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o $(OBJECTS)