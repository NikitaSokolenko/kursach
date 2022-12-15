CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS= -lpthread -lcrypto++
SOURCES=main.cpp Auth.cpp interface.cpp WebManager.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
