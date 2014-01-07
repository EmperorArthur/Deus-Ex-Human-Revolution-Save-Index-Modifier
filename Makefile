#Quick and dirty Makefile
#Public Domain Arthur Moore 213
#Pretty much used this as a template:        http://mrbook.org/tutorials/make/

CC=g++
CFLAGS=-std=c++11 -c -Wall -Wextra
LDFLAGS=-std=c++11
SOURCES=indexer.cpp indexfile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=indexer.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@