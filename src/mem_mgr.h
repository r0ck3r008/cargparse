#ifndef MEM_MGR_H
#define MEM_MGR_H

#include"cargparse.h"

void *alloc(char *, int);
void dealloc(char *, int , void *);
struct arg *init_arg_struct(int);
void deinit_arg_struct(struct arg *, int);
void alloc_start_node(struct arg *);
void add_node(struct arg *, struct arg *);
void del_list(struct arg *);

#endif
