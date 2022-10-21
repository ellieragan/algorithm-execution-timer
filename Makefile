#Makefile for run.c
#Ellie Boyd

S = ../support
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$S

OBJS = run.o

.PHONY: all clean

all: run

run: $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f run
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core
	rm -f vgcore.*
	rm all_files.out
	rm -f *.swp
