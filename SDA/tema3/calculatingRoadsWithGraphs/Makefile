#POPESCU Matei-315CB

build:
	gcc -g -std=c99 main.c functii.c -o tema3

run:
	./tema3 1

clean:
	rm tema3
valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all  --track-origins=yes ./tema3 1
