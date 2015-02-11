#include "const.h"

#ifndef tree_h
#define tree_h

void print(struct node * a);
struct node * new_node(void);
struct node * new_tree(int freq[size], struct node * leaves[size], int n);
void cut_tree(struct node * a);

#endif // tree_h
