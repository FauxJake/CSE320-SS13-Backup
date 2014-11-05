#makefile for project 06
#

#CC = gcc
#CFLAGS = -g -Wall

proj06: support.o driver.o /user/cse320/Projects/project06.support.h
	gcc -o proj06 proj06.support.o proj06.driver.o 

driver.o: proj06.driver.c
	gcc -c proj06.driver.c 

support.o: proj06.support.c
	gcc -c proj06.support.c 

clean:
	rm -f proj06.support.o 
	rm -f proj06.driver.o
	rm -f proj06
