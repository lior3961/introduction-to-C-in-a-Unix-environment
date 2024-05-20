# Target to build the labA executable
all: labAexec

# Rule to link the 'labA' executable
labAexec: main.o
	gcc -m32 -g -Wall -o labAexec main.o

# Rule to compile C source files into object files
main.o: main.c
	gcc -m32 -g -Wall -c -o main.o main.c

# Phony target to clean up object files and the executable
.PHONY: clean
clean:
	rm -f *.o labAexec
