CC=gcc
LD=$(CC)
CFLAGS=-I./include -DDEBUG -g
LDFLAGS=

all: hashtable

hashtable: src/hashtbl.o test/main.o
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o src/*.o test/*.o hashtable
