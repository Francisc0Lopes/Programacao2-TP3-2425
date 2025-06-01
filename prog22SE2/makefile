
prog22: prog22.o wordSearch.o wordsAll.o
	gcc -Wall -o prog22 prog22.o wordSearch.o wordsAll.o  

prog22.o: prog22.c wordSearch.h wordsAll.h
	gcc -Wall -c prog22.c

wordSearch.o: wordSearch.c wordSearch.h
	gcc -c wordSearch.c

wordsAll.o: wordsAll.c wordsAll.h
	gcc -Wall -c wordsAll.c
	
clean:
	rm -f prog22 *.o
	
