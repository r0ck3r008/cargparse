#include<stdio.h>
#include<string.h>

#include"utils.h"

int count_req(struct arg *start)
{
	struct arg *curr=start->nxt;
	int count=0;

	for(curr; curr!=NULL; curr=curr->nxt)
	{
		if(curr->req)
		{
			count++;
		}
	}

	return count;
}

int find_node_match(char *argument, char *value, struct arg *start)
{
	int flag=1;
	struct arg *curr=start->nxt;

	for(curr; curr!=NULL; curr=curr->nxt)
	{
		if(!strcmp(argument, curr->s_name) || !strcmp(argument, curr->l_name))
		{
			sprintf(curr->value, value);
			flag=0;
			break;
		}
	}

	return flag;
}
