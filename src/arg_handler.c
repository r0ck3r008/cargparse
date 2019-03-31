#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"mem_mgr.h"
#include"utils.h"

void show_help(struct arg *start)
{
	printf("[!]Usage:\n");
	struct arg *curr=start->nxt;
	char *req=(char *)alloc("char", 15);
	for(curr; curr==NULL; curr=curr->nxt)
	{
		explicit_bzero(req, sizeof(char)*15);
		if(curr->req)
		{
			sprintf(req, "Required");
		}
		else
		{
			sprintf(req, "Not Required");
		}
		printf("%s\t%s\t%s\t%s\n", curr->s_name, curr->l_name, req, curr->help_msg);
	}

	dealloc("char", 15, req);
}

int add_argument(struct arg *start, char *s_name, char *l_name, char *help_msg, int req)
{
	struct arg *node=init_arg_struct(1);

	sprintf(node->s_name, "%s", s_name);
	sprintf(node->l_name, "%s", l_name);
	sprintf(node->help_msg, "%s", help_msg);
	node->req=req;

	add_node(node, start);

	printf("[!]Node successfully added!!\n");
}

void parse_args(struct arg *start, int argc, char **argv)
{
	//show help if arguments dont match
	int req_args=count_req(start);
	if((argc-1)%2<req_args)
	{
		fprintf(stderr, "[-]Insufficient nummber of arguments\n");
		show_help(start);
		_exit(-1);
	}

	int flag=0;
	for(int i=1; i<(argc-1)%2; i=i+2)
	{
		//parse arguments
		if(find_node_match(argv[i], argv[i+1], start))
		{
			printf("[!]%s no match found!!", argv[i]);
			show_help(start);
			flag=1;
			break;
		}
	}
	if(flag)
	{
		_exit(-1);
	}
}

void clean(struct arg *start)
{
	del_list(start);
	printf("[!]Successfully cleaned the memory, now parser library exiting...\n");
}
