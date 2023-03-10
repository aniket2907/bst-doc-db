

#ifndef LISTDB_H
#define LISTDB_H

int   listdb_init           ( void );
int   listdb_add            ( char *name, int word_count );
int   listdb_get_word_count ( int doc_id );
char* listdb_get_name       ( int doc_id );
void  listdb_stat           ( void );
void  listdb_quit           ( void );

#endif
