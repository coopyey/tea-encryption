CC=gcc
CFLAGS=-g -Wall -std=c11
LIBS=-lssl -lcrypto
TAR=prog

OUT=output
CBC=output/cbc
OFB=output/ofb
PLAIN=*_plain_*.txt
CIPHER=*_cipher_*.txt

.PHONY: default all clean

default: $(TAR)
all: default cleanobj

OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
HEADERS=$(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TAR) $(OBJ)

$(TAR): $(OBJ)
	$(CC) $(OBJ) -Wall -o $(OUT)/$@ $(LIBS)

clean:
	-rm -f *.o
	-rm -f $(OUT)/$(TAR)
	-rm -f $(CBC)/$(CIPHER) $(CBC)/$(PLAIN) $(OFB)/$(CIPHER) $(OFB)/$(PLAIN)

rebuild: clean all

cleanobj:
	-rm -f *.o
	-rm -f $(CBC)/$(CIPHER) $(CBC)/$(PLAIN) $(OFB)/$(CIPHER) $(OFB)/$(PLAIN)
