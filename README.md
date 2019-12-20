# The Argument Parser Library for C/C++


#### Objective
This project can be added as a submodule to any other project for providing __commandline argument__ parsing capabilities, like python's argparse[1] library

#### Dependencies
* GNU GCC (test enviornment, might work with other tool chains)
* GNU make (for compilation)

#### Compilation
* Make the library
    ```bash
    make
    ```
* Make the example binary
    ```bash
    make example_bin
    ```

#### Usage
Basic usage is demonstrated in example/example_usage.c file and the corresponding Makefile

#### Architecture Overview
* The main cargparse.h file imports the src/global_defs.h header file
* The src/global_defs.h defines the argument struct and the Public API functions
* The Arguments along with their attributes like short_name, long_name, help etc. are kept as nodes of a bi-directional linked list

#### References
[1] [Argparse Python](https://docs.python.org/3/library/argparse.html)
