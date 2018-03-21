CC=gcc
CFLAGS=-g -Wall
LIBS=
TAR=prog

.PHONY: default all clean

default: $(TAR)
all: default cleanobj

OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
HEADERS=$(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TAR) $(OBJ)

$(TAR): $(OBJ)
	$(CC) $(OBJ) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TAR)

rebuild: clean all

cleanobj:
	-rm -f *.o