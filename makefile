.PHONY: all

all:
	gcc -std=gnu99 -Wall teste.c -o teste.out -lm
	
fclean:
	rm *.out
