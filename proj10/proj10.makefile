#
# makefile for Project 10
#

CC = gcc
CFLAGS = -g -Wall

proj10: proj10.support.o \
 /user/cse320/Projects/project10.driver.o\
  /user/cse320/Projects/project10.interface.h
	gcc -o proj10 proj10.support.o /user/cse320/Projects/project10.driver.o /user/cse320/lib/reglib.o

support.o: proj10.support.s 
	gcc -c proj10.support.s

clean:
	rm -f support.o
	rm -f proj10