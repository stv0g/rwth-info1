SRCS = $(wildcard src/*.c)
PROGS = $(patsubst src/%.c,%,$(SRCS))

CFLAGS += -g -Wall -O0 -ansi -static
VPATH = src/

all: $(PROGS)

%: src/%.c
	$(CC) $(CFLAGS) $< -o bin/$@

clean:
	rm -f bin/* src/*.save
	
