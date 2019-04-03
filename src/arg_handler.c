#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"global_defs.h"
#include"mem_mgr.h"
#include"utils.h"

struct arg *init_lib()
{
	printf("[!]Starting cargparse library...\n");
	struct arg *start=alloc_start_node();
	return start;
}

void show_help(struct arg *start)
{
	printf("[!]Usage:\n");
	struct arg *curr=start->nxt;
	char *req=(char *)alloc("char", 15);
	for(curr; curr!=NULL; curr=curr->nxt)
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
	clean(start);
}

void add_argument(struct arg *start, char *s_name, char *l_name, char *help_msg, int req)
{
	struct arg *node=init_arg_struct(1);

	sprintf(node->s_name, "%s", s_name);
	sprintf(node->l_name, "%s", l_name);
	sprintf(node->help_msg, "%s", help_msg);
	node->req=req;

	add_node(node, start);
}

void parse_args(struct arg *start, int argc, char **argv)
{
	//show help if arguments dont match
	int req_args=count_req(start);
	int arg_grps=(argc-1)/2;

	int flag=0;
	for(int i=0; i/2<arg_grps; i=i+2)
	{
		int ret=find_node_match(argv[i+1], argv[i+2], start);
		
		switch(ret)
		{
			case 0:
				{
					fprintf(stderr, "[-]No match for argument {%s}\n", argv[i+1]);
					show_help(start);
					//exit stratergy
					i=arg_grps*2;
					flag=1;
					break;
				}
			case 2:
				{
					req_args--;
				}
		}

		if((i/2==(arg_grps-1)) && req_args!=0)
		{
			fprintf(stderr, "[-]Insufficient number of required arguments!\n");
			show_help(start);
			//exit stratergy
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
	printf("[!]Cleaning parser library now... ");
	del_list(start);
	printf("Done!\n");
}
