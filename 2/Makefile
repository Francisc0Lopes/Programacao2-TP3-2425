CC = gcc
CFLAGS = -Wall -g
OBJ = modules/vecloc.o prog32.o
TARGET = prog32

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ ../1/modules/textread.o



modules/vecloc.o: modules/vecloc.c modules/vecloc.h
	$(CC) $(CFLAGS) -c modules/vecloc.c -o modules/vecloc.o

prog32.o: prog32.c modules/vecloc.h ../1/modules/textread.h
	$(CC) $(CFLAGS) -c prog32.c -o prog32.o

clean:
	rm -f $(OBJ) prog32.o $(TARGET)