CC=gcc
CFLAGS=-Wall -O2

INCLUDES = src/includes/page_operations.h src/includes/table.h

main: table.o page_operations.o main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $^

table.o: src/base_structures/table.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ src/base_structures/table.c

page_operations.o: src/io_operations/page_operations.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ src/io_operations/page_operations.c

clean:
	rm -f *.o
