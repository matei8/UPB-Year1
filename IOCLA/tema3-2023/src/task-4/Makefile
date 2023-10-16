.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

%.o: %.asm
	nasm -f elf $^ -o $@

%.o: %.c
	gcc -c -g -m32 $^ -o $@

%.o: _utils/%.c
	gcc -c -g -m32 $^ -o $@

checker: checker-binary-tree.o binary-tree_1.o binary-tree_2.o binary-tree_3.o bst.o
	gcc -no-pie -m32 -g $^ -o $@

clean:
	rm -f checker *.o
	rm -f out/*.out
