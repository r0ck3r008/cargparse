#ifndef MEM_MGR_H
#define MEM_MGR_H

#include"global_defs.h"

void *alloc(char *, int);
void dealloc(char *, int , void *);
int alloc_start_node(struct arg *);
void add_node(struct arg *, struct arg *);
void del_list(struct arg *);

#endif
