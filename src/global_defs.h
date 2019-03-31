#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

struct arg
{
	int req;
	char *s_name;	//5
	char *l_name;	//15
	char *help_msg; //50
	char *value;	//10
	struct arg *nxt, *prev;
};

#endif
