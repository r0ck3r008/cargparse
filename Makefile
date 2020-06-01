all: libcargparse.so

libcargparse.so: src/Makefile
	make -C src

example_bin: example/Makefile
	make -C example

clean:
	make -C src/ clean
	make -C example/ clean
