#include<stdio.h>
#include<string.h>

#include"utils.h"

int _count_req(struct arg *start)
{
	struct arg *curr=start->nxt;
	int count=0;

	for(curr; curr!=NULL; curr=curr->nxt){
		if(curr->req){
			count++;
		}
	}

	return count;
}

int _find_node_match(char *argument, char *value, struct arg *start)
{
	int flag=0;
	struct arg *curr=start->nxt;

	for(curr; curr!=NULL; curr=curr->nxt){
		if(!strcmp(argument, curr->s_name) || !strcmp(argument,
								curr->l_name)){
			sprintf(curr->value, value);
			if(curr->req){
				flag=2;
			}else{
				flag=1;
			}
			break;
		}
	}

	return flag;
}
