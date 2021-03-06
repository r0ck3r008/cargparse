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
	struct arg *start=_alloc_start_node();
	return start;
}

void show_help(struct arg *start)
{
	printf("[!]Usage:\n");
	struct arg *curr=start->nxt;
	char *req=(char *)_alloc("char", 15);
	for(curr; curr!=NULL; curr=curr->nxt){
		explicit_bzero(req, sizeof(char)*15);
		if(curr->req)
		{
			sprintf(req, "Required");
		}
		else
		{
			sprintf(req, "Optional");
		}
		printf("%s\t%s\t%s\t%s\n", curr->s_name,
			curr->l_name, req, curr->help_msg);
	}

	_dealloc("char", 15, req);
	clean(start);
}

void add_argument(struct arg *start, char *s_name, char *l_name,
			char *name, char *help_msg, int req)
{
	struct arg *node=_alloc("struct arg", 1);
	node->s_name=_char_copy(s_name);
	node->l_name=_char_copy(l_name);
	node->name=_char_copy(name);
	node->help_msg=_char_copy(help_msg);

	_add_node(node, start);
}

void parse_args(struct arg *start, int argc, char **argv)
{
	//show help if arguments dont match
	int req_args=_count_req(start);
	int arg_grps=(argc-1)/2;

	int flag=0;
	for(int i=0; i/2<arg_grps; i=i+2){
		int ret=_find_node_match(argv[i+1], argv[i+2], start);

		switch(ret){
		case 0:
			fprintf(stderr, "[-]No match for argument\
						{%s}\n", argv[i+1]);
			show_help(start);
			//exit stratergy
			i=arg_grps*2;
			flag=1;
			break;
		case 2:
			req_args--;
		}

		if((i/2==(arg_grps-1)) && req_args!=0){
			fprintf(stderr, "[-]Insufficient number of required\
				arguments!\n");
			show_help(start);
			//exit stratergy
			flag=1;
			break;
		}

	}
	if(flag){
		_exit(-1);
	}
}

char *find_arg_val(struct arg *start, char *name)
{
	struct arg *curr=start->nxt;
	char *ret=NULL;

	for(curr; curr!=NULL; curr=curr->nxt){
		if(!strcmp(curr->name, name)){
			ret=curr->value;
			break;
		}
	}

	return ret;
}

void clean(struct arg *start)
{
	printf("[!]Cleaning parser library now... ");
	_del_list(start);
	printf("Done!\n");
}
