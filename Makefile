all: libcargparse.so

libcargparse.so: src/Makefile
	make -C src
	make clean_objs

example_bin: libcargparse.so example/Makefile
	make -C example

clean_objs:
	make -C src/ clean
	make -C example/ clean
clean:
	rm -f ./libcargparse.so
