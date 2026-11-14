CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-ljpeg
SOURCES= mandel.c jpegrw.c mandelMovie.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLES=mandel mandelmovie

all: $(SOURCES) $(EXECUTABLES)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

mandel: mandel.o jpegrw.o
	$(CC) mandel.o jpegrw.o $(LDFLAGS) -o $@

mandelmovie: mandelMovie.o
	$(CC) mandelMovie.o $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLES) *.d



