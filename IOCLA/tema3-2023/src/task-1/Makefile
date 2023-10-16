.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

%.o: %.asm
	nasm -f elf $^ -o $@

%.o: %.c
	gcc -c -g -m32 $^ -o $@

checker: check-vowels.o reverse_vowels.o
	gcc -no-pie -m32 -g $^ -o $@

clean:
	rm -f checker *.o
	rm -f out/*.out