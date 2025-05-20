CC = gcc
CFLAGS = -Wall -g
OBJ = modules/textread.o prog31.o
TARGET = prog31

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

textread.o: modules/textread.c modules/textread.h
	$(CC) $(CFLAGS) -c modules/textread.c

prog31.o: prog31.c
	$(CC) $(CFLAGS) -c prog31.c

clean:
	rm -f $(OBJ) $(TARGET)