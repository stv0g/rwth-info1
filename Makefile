SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

CFLAGS += -g -Wall -O0

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

clean:
	rm -f *.o *.save $(PROGS)
