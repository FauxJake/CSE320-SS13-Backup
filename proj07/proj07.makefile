#
# makefile for Project 07
#

CC = gcc
CFLAGS = -g -Wall

proj07: proj07.support.o \
 /user/cse320/Projects/project07.driver.o\
  /user/cse320/Projects/project07.hardware.h\
   /user/cse320/Projects/project07.support.h
	gcc -o proj07 proj07.support.o /user/cse320/Projects/project07.driver.o

support.o: proj07.support.c
	gcc -c proj07.support.c 

clean:
	rm -f support.o
	rm -f proj07