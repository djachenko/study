#ifndef list_h
#define list_h

struct list * new_list(void);
int empty(struct list * a);
void print_list(struct list * src);
void list_add(struct list ** to, int a);
struct list * list_dup(struct list * src);
void list_cat(struct list ** to, struct list * from);
int list_get(struct list ** source);
int list_nget(struct list ** source, int n);
int list_tailget(struct list ** source);
int list_len(struct list * a);
void list_clear(struct list ** source);

#endif //list_h
