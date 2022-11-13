CC=gcc
CFLAGS=-Wall -O2

INCLUDES = src/includes/page_operations.h src/includes/table.h

# main: table.o
# 	$(CC) $(CFLAGS) -o $@ $^

table.o: src/base_structures/table.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o table.o src/base_structures/table.c
