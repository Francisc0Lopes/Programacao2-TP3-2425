prog32: prog32.o modules/vecloc.o ../1/modules/textread.o
	gcc -Wall -g -o prog32 prog32.o modules/vecloc.o ../1/modules/textread.o

prog32.o: prog32.c modules/vecloc.h ../1/modules/textread.h
	gcc -Wall -g -c prog32.c

modules/vecloc.o: modules/vecloc.c modules/vecloc.h
	gcc -Wall -g -c modules/vecloc.c -o modules/vecloc.o

../1/modules/textread.o: ../1/modules/textread.c ../1/modules/textread.h
	gcc -Wall -g -c ../1/modules/textread.c -o ../1/modules/textread.o

clean:
	rm -f prog32 *.o modules/*.o ../1/modules/textread.o