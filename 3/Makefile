prog33: prog33.o modules/tree.o modules/allFuncs.o ../2/modules/vecloc.o ../1/modules/textread.o
	gcc -Wall -g -o prog33 prog33.o modules/tree.o modules/allFuncs.o ../2/modules/vecloc.o ../1/modules/textread.o

prog33.o: prog33.c modules/tree.h modules/allFuncs.h ../2/modules/vecloc.h ../1/modules/textread.h
	gcc -Wall -g -c prog33.c

modules/tree.o: modules/tree.c modules/tree.h ../2/modules/vecloc.h
	gcc -Wall -g -c modules/tree.c -o modules/tree.o

modules/allFuncs.o: modules/allFuncs.c modules/allFuncs.h
	gcc -Wall -g -c modules/allFuncs.c -o modules/allFuncs.o

../2/modules/vecloc.o: ../2/modules/vecloc.c ../2/modules/vecloc.h
	gcc -Wall -g -c ../2/modules/vecloc.c -o ../2/modules/vecloc.o

../1/modules/textread.o: ../1/modules/textread.c ../1/modules/textread.h
	gcc -Wall -g -c ../1/modules/textread.c -o ../1/modules/textread.o

clean:
	rm -f prog33 *.o modules/*.o ../2/modules/vecloc.o ../1/modules/textread.o