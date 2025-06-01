#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "wordSearch.h"
#include "locale.h"


int wordCheck( char *word, void *context ){	
	char *pointer = context;
	return strcoll(word,pointer)==0;
} 
