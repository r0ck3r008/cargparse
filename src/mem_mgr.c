#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"mem_mgr.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char"))
	{
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	}
	else if(!strcmp(type, "struct arg"))
	{
		ret=(struct arg *)malloc(sizeof(struct arg)*size);
		explicit_bzero(ret, sizeof(struct arg)*size);
	}

	if(ret==NULL)
	{
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n", size, type);
		_exit(-1);
	}

	return ret;
}

void dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char"))
	{
		explicit_bzero(buf, sizeof(char)*size);
	}
	else if(!strcmp(type, "struct arg"))
	{
		explicit_bzero(buf, sizeof(struct arg)*size);
	}
	free(buf);
}

struct arg *init_arg_struct(int flag)
{
	struct arg *ret=(struct arg *)alloc("struct arg", 1);

	if(flag)
	{
		ret->help_msg=(char *)alloc("char", 50);
	}
	ret->s_name=(char *)alloc("char", 5);
	ret->l_name=(char *)alloc("char", 15);
	ret->value=(char *)alloc("char", 10);

	return ret;
}

void deinit_arg_struct(struct arg *buf, int flag)
{
	if(flag)
	{
		dealloc("char", 50, buf->help_msg);
	}

	dealloc("char", 5, buf->s_name);
	dealloc("char", 15, buf->l_name);
	dealloc("char", 10, buf->value);
	dealloc("struct arg", 1, buf);
}

void alloc_start_node(struct arg *start)
{
	start=init_arg_struct(0);
	sprintf(start->s_name, "-h");
	sprintf(start->l_name, "--help");
	start->help_msg=NULL;
	sprintf(start->value, "INIT");
	start->req=-1;
	start->prev=NULL;
}

void add_node(struct arg *new, struct arg *start)
{
	static struct arg *curr;
	struct arg *tmp=new;

	if(start==NULL)
	{
		alloc_start_node(start);
		start->nxt=tmp;
		tmp->prev=start;
		tmp->nxt=NULL;
	}
	else
	{
		curr->nxt=tmp;
		tmp->prev=curr;
		tmp->nxt=NULL;
	}
	curr=tmp;
	printf("[!]Node with s_name %s successfully added\n", curr->s_name);
}

void del_list(struct arg *start)
{
	struct arg *curr=start->nxt;
	for(curr; curr!=NULL; curr=curr->nxt)
	{
		curr->prev->nxt=curr->nxt;
		if(curr->nxt!=NULL)
		{
			//not last node
			curr->nxt->prev=start;
		}
		deinit_arg_struct(curr, 1);
	}
	deinit_arg_struct(start, 0);
	printf("[!]Successful deallocation of the chain!\n");
}
