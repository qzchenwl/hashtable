all: hashtable

hashtable: hashtbl.o main.o
	gcc hashtbl.o main.o -o hashtable

hashtbl.o: hashtbl.c
	gcc -I. -c hashtbl.c

main.o: main.c
	gcc -I. -c main.c

clean:
	rm -f *.o hashtable
