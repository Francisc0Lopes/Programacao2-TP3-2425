
#ifndef ALLFUNCS_H
#define ALLFUNCS_H
#define MAX 1024

enum ClassId { S_ASC, S_INIT, S_CONT };
enum ClassId utf8Class(char c);


int utf8NormFirst(char str[]);
void utf8NormAll(char str[]);


int wordProcess( char *str, int (*action)( char *word, void *context ),void *context ); 
int wordPrint( char *word, void *context ); 


int wordCheck( char *word, void *context);


#endif


