#ifndef TEXTREAD_H
#define TEXTREAD_H

int textStart( char *fileName ); 
char *textSequenceLine( long *storeOffset ); 
char *textLocatedLine( long offset ); 
void textEnd( void ); 


#endif 
