#include<stdio.h>
#include<unistd.h>

#include"cargparse/cargparse.h"

int main(int argc, char *argv[])
{
	struct arg *args=init_lib();

	add_argument(args, "-u", "--uds_sock", "uds_sock",
			"The URI of uds sock", 1);
	add_argument(args, "-p", "--pipe_path", "pipe_path",
			"The URI of pipe", 0);

	if(argc<3 || argc>5){
		show_help(args);
		_exit(-1);
	}

	parse_args(args, argc, argv);

	printf("[!]The value of UDS sock URI is:\t%s\n",
		find_arg_val(args, "uds_sock"));
	if(argc==5){
		printf("[!]The value of pipe URI is: \t%s\n",
			find_arg_val(args, "pipe_path"));
	}

	clean(args);
}
