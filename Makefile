CC=gcc
LD=$(CC)
CFLAGS=-I. -DDEBUG
LDFLAGS=

all: hashtable

hashtable: hashtbl.o main.o
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o hashtable

test: hashtable input.txt
	./hashtable < input.txt | grep coll
