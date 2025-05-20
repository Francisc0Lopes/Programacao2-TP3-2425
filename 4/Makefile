CC = gcc
CFLAGS = -Wall -g
OBJ = modules/hashtable.o ../2/modules/vecloc.o ../1/modules/textread.o prog34.o
TARGET = prog34

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

prog34.o: prog34.c modules/hashtable.h ../2/modules/vecloc.h ../1/modules/textread.h
	$(CC) $(CFLAGS) -c prog34.c

modules/hashtable.o: modules/hashtable.c modules/hashtable.h ../2/modules/vecloc.h	
	$(CC) $(CFLAGS) -c modules/hashtable.c -o modules/hashtable.o

../2/modules/vecloc.o: ../2/modules/vecloc.c ../2/modules/vecloc.h
	$(CC) $(CFLAGS) -c ../2/modules/vecloc.c -o ../2/modules/vecloc.o

../1/modules/textread.o: ../1/modules/textread.c ../1/modules/textread.h
	$(CC) $(CFLAGS) -c ../1/modules/textread.c -o ../1/modules/textread.o

clean:
	rm -f $(OBJ) $(TARGET)