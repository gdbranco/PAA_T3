.PHONY: all

all:
	gcc -std=gnu99 -Wall prova_110012470_Guilherme.c -o prova_110012470_Guilherme.out -lm
	
fclean:
	rm *.out
