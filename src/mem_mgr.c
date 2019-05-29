#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"mem_mgr.h"

void *_alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")){
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	}else if(!strcmp(type, "struct arg")){
		ret=(struct arg *)malloc(sizeof(struct arg)*size);
		explicit_bzero(ret, sizeof(struct arg)*size);
	}

	if(ret==NULL){
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n",
			size, type);
		_exit(-1);
	}

	return ret;
}

void _dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char")){
		explicit_bzero(buf, sizeof(char)*size);
	}else if(!strcmp(type, "struct arg")){
		explicit_bzero(buf, sizeof(struct arg)*size);
	}
	free(buf);
}

struct arg *_init_arg_struct(int flag)
{
	struct arg *ret=(struct arg *)_alloc("struct arg", 1);

	if(flag){
		ret->help_msg=(char *)_alloc("char", 50);
	}
	ret->s_name=(char *)_alloc("char", 5);
	ret->l_name=(char *)_alloc("char", 15);
	ret->value=(char *)_alloc("char", 10);

	return ret;
}

void _deinit_arg_struct(struct arg *buf, int flag)
{
	if(flag){
		_dealloc("char", 50, buf->help_msg);
	}

	_dealloc("char", 5, buf->s_name);
	_dealloc("char", 15, buf->l_name);
	_dealloc("char", 10, buf->value);
	_dealloc("struct arg", 1, buf);
}

struct arg *_alloc_start_node()
{
	//allocate mem
	struct arg *start=_init_arg_struct(0);

	//initiate pointers
	start->help_msg=NULL;
	start->nxt=NULL;
	start->prev=NULL;

	//add values
	sprintf(start->s_name, "-h");
	sprintf(start->l_name, "--help");
	sprintf(start->value, "INIT");
	start->req=0;

	//return
	return start;
}

void _add_node(struct arg *node, struct arg *curr)
{
	for(curr; curr->nxt!=NULL; curr=curr->nxt);

	curr->nxt=node;
	node->prev=curr;
	node->nxt=NULL;
}

void _del_list(struct arg *start)
{
	struct arg *curr=start->nxt;
	for(curr; curr!=NULL; curr=curr->nxt){
		curr->prev->nxt=curr->nxt;
		if(curr->nxt!=NULL){
			//not last node
			curr->nxt->prev=start;
		}
		_deinit_arg_struct(curr, 1);
	}
	_deinit_arg_struct(start, 0);
}
