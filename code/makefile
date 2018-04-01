CC=gcc
CFLAGS=-g -Wall -std=c11
LIBS=-lssl -lcrypto
TAR=prog

CBC=cbc
OFB=ofb
PLAIN=*_p_*.txt
CIPHER=*_c_*.txt

.PHONY: default all clean

default: $(TAR)
all: default cleanobj

OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
HEADERS=$(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TAR) $(OBJ)

$(TAR): $(OBJ)
	$(CC) $(OBJ) -Wall -o $@ $(LIBS)

clean:
	-rm -f *.o
	-rm -f $(TAR)
	-rm -f $(CBC)/$(CIPHER) $(CBC)/$(PLAIN) $(OFB)/$(CIPHER) $(OFB)/$(PLAIN)

rebuild: clean all

cleanobj:
	-rm -f *.o
	-rm -f $(CBC)/$(CIPHER) $(CBC)/$(PLAIN) $(OFB)/$(CIPHER) $(OFB)/$(PLAIN)
