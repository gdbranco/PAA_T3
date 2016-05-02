.PHONY: all

all:
	gcc -std=gnu99 -Wall main.c -o trab3.out -lm
	
fclean:
	rm *.out
