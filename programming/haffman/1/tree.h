#ifndef tree_h_
#define tree_h

#include "types.h"

void print(struct node * a);
struct node * new_node(void);
struct node * new_tree(struct node * leaves[256], int n);
void cut_tree(struct node * a);

#endif // tree_h
