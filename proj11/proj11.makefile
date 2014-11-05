# Makefile for proj11

#CC = gcc
#CFLAGS = -g -Wall

proj09: proj11.driver.c proj11.support.s /user/cse320/Projects/project11.support.h 
	gcc -lm -g -Wall -o proj11 proj11.driver.c proj11.support.s /user/cse320/lib/reglib.o

clean:
	rm -f proj11.support.o
	rm -f proj11.driver.o
	rm -f proj11
