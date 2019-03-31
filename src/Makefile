ALL_OBJS= arg_handler.o mem_mgr.o utils.o
LINKER_FLAGS= -shared -o
COMPILER_FLAGS= -g -fpic -c

all: libcargparse.so clean_objs

libcargparse.so: ${ALL_OBJS}
	gcc ${LINKER_FLAGS} ./libcargparse.so ${ALL_OBJS}

arg_handler.o: arg_handler.c
	gcc ${COMPILER_FLAGS} arg_handler.c

mem_mgr.o: mem_mgr.c
	gcc ${COMPILER_FLAGS} mem_mgr.c

utils.o: utils.c
	gcc ${COMPILER_FLAGS} utils.c

clean_objs:
	rm ./*.o

clean:
	rm ./libcargparse.so
