COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -Lcargparse/src -lcargparse -o
ALL_OBJS := example_usage.o

all: example_bin clean_objs

example_bin: ${ALL_OBJS}
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} example_bin

example_usage.o: example_usage.c
	${COMPILER} ${COMPILER_FLAGS} example_usage.c

clean_objs: ${ALL_OBJS}
	rm -f ./example_usage.o

clean:
	rm -f example_bin
