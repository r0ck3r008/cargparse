#ifndef CARGPARSE_H
#define CARGPARSE_H

struct arg
{
	int req;
	char *s_name;	//5
	char *l_name;	//15
	char *help_msg; //50
	char *value;	//10
	struct arg *nxt, *prev;
};

void show_help(struct arg *);
void add_argument(struct arg *, char *, char *, char *, int);
void parse_args(struct arg *, int, char **);
void clean(struct arg *);

#endif
