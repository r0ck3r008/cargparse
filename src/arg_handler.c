#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"mem_mgr.h"

struct arg *init_lib()
{
	printf("[!]Starting argument library...\n");
	struct arg *start;
	return start;
}

void show_help(struct arg *start)
{
	printf("[!]Usage:\n");
	struct arg *curr=start->nxt;
	char *req=(char *)alloc("char", 15, 0);
	for(curr; curr->nxt!=NULL; curr=curr->nxt)
	{
		explicit_bzero(req, sizeof(char)*15);
		if(curr->req)
		{
			sprintf(req, "Required");
		}
		else
		{
			sprintf(ret, "Not Required");
		}
		printf("%s\t%s\t%s\t%s\n", curr->s_name, curr->l_name, req, curr->help_msg);
	}

	dealloc("char", 15, req, 0);
}

int add_argument(struct arg *start, char *s_name, char *l_name, char *help_msg, int req)
{
	struct arg *node=(struct arg *)alloc("struct arg", 5, 1);

	sprintf(node->s_name, "%s", s_name);
	sprintf(node->l_name, "%s", l_name);
	sprintf(node->help_msg, "%s", help_msg);
	node->req=req;

	add_node(node, start);

	printf("[!]Node successfully added!!\n");
}

void parse_args(struct arg *start, int argc, char **argv)
{
	int req_args=count_req(start);
}

void clean(struct arg *start)
{
	del_list(start);
	printf("[!]Successfully cleaned the memory, now parser library exiting...\n");
}
