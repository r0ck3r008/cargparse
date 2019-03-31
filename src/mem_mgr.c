#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void *alloc(char *type, int size, int flag)
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
		if(flag)
		{
			ret->s_name=(char *)alloc("char", 5, 0);
			ret->l_name=(char *)alloc("char", 15, 0);
			ret->help_msg=(char *)alloc("char", 50, 0);
		}
		ret->value=(char *)alloc("char", 10, 0);
	}

	if(ret==NULL)
	{
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n", size, type);
		_exit(-1);
	}

	return ret;
}

void dealloc(char *type, int size, void *buf, int flag)
{
	if(!strcmp(type, "char"))
	{
		explicit_bzero(buf, sizeof(char)*size);
	}
	else if(!strcmp(type, "char"))
	{
		if(flag)
		{
			dealloc("char", 5, buf->s_name, 0);
			dealloc("char", 15, buf->l_name, 0);
			dealloc("char", 50, buf->help_msg, 0);
		}
		dealloc("char", 10, buf->value, 0);
		explicit_bzero(buf, sizeof(struct arg)*size);
	}
	free(buf);
}

void alloc_start_node(struct arg *start)
{
	start=(struct arg *)alloc("struct arg", 1, 0);
	start->s_name=NULL;
	start->l_name=NULL;
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
		dealloc("struct arg", 1, curr, 1);
	}
	dealloc("struct arg", 1, start, 0);
	printf("[!]Successful deallocation of the chain!\n");
}

int count_req(struct arg *start)
{
	struct arg *curr=start->nxt;
	int count=0;

	for(curr; curr->nxt!=NULL; curr=curr->nxt)
	{
		if(curr->req)
		{
			count++;
		}
	}

	return count;
}
