prog31: prog31.o modules/textread.o
	gcc -Wall -o prog31 prog31.o modules/textread.o

prog31.o: prog31.c modules/textread.h
	gcc -Wall -c prog31.c

modules/textread.o: modules/textread.c modules/textread.h
	gcc -Wall -c modules/textread.c -o modules/textread.o

clean:
	rm -f prog31 *.o modules/*.o