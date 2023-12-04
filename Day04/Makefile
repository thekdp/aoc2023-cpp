CC=g++
CFLAGS= -c -Wall -g
HEADERS=
SOURCES= main.cpp card.cpp cardpile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aoc

all: $(SOURCES) $(EXECUTABLE) clean
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o $(OBJECTS)