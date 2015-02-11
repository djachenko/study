#ifndef tree_h_
#define tree_h

#include "types.h"

void fprint_tree(struct node * a, FILE * dest);
void print_tree(struct node * a);
struct node * new_node(void);
struct node * new_tree(struct node * leaves[256], int n);
struct node * fread_tree(FILE * stream);
struct node * read_tree();
void cut_tree(struct node * a);
int tree_height(struct node * a);

#endif // tree_h
