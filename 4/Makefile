prog34: prog34.o modules/hashtable.o ../3/modules/allFuncs.o ../2/modules/vecloc.o ../1/modules/textread.o
	gcc -Wall -g -o prog34 prog34.o modules/hashtable.o ../3/modules/allFuncs.o ../2/modules/vecloc.o ../1/modules/textread.o

prog34.o: prog34.c modules/hashtable.h ../3/modules/allFuncs.h ../2/modules/vecloc.h ../1/modules/textread.h
	gcc -Wall -g -c prog34.c

modules/hashtable.o: modules/hashtable.c modules/hashtable.h ../2/modules/vecloc.h
	gcc -Wall -g -c modules/hashtable.c -o modules/hashtable.o

../3/modules/allFuncs.o: ../3/modules/allFuncs.c ../3/modules/allFuncs.h
	gcc -Wall -g -c ../3/modules/allFuncs.c -o ../3/modules/allFuncs.o

../2/modules/vecloc.o: ../2/modules/vecloc.c ../2/modules/vecloc.h
	gcc -Wall -g -c ../2/modules/vecloc.c -o ../2/modules/vecloc.o

../1/modules/textread.o: ../1/modules/textread.c ../1/modules/textread.h
	gcc -Wall -g -c ../1/modules/textread.c -o ../1/modules/textread.o

clean:
	rm -f prog34 *.o modules/*.o ../3/modules/allFuncs.o ../2/modules/vecloc.o ../1/modules/textread.o