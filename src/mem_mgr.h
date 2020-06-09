#ifndef MEM_MGR_H
#define MEM_MGR_H

#include"global_defs.h"

void *_alloc(char *, int);
char *_char_copy(char *);
void _dealloc(char *, int , void *);
void _deinit_arg_struct(struct arg *, int);
struct arg *_alloc_start_node();
void _add_node(struct arg *, struct arg *);
void _del_list(struct arg *);

#endif
