EXECUTABLE=aes_crack

CC=g++
CFLAGS=-c -Wall
LDFLAGS=
LDLIBS =-lcrypto
SOURCES=aes_crack.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run :
	./aes_crack

clean :
	$(RM) $(EXECUTABLE)
	$(RM) $(OBJECTS)
