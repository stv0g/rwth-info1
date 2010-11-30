SRCS = $(wildcard src/*.c)
PROGS = $(patsubst src/%.c,%,$(SRCS))

CFLAGS += -g -Wall -O0 -ansi
VPATH = src/

all: $(PROGS)

conway: src/conway.c
	$(CC) $(CFLAGS) -std=gnu99 src/conway.c -o bin/conway -lcurses

%: src/%.c
	$(CC) $(CFLAGS) $< -o bin/$@

clean:
	rm -f bin/* src/*.save
	
