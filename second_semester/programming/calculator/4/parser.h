#ifndef parser_h
#define parser_h

double constance(char * a);
void parser_right(int c, struct stream * stream);
struct hashtable * parser_left(char * name);

#endif
