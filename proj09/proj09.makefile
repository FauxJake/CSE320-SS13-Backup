#CC = gcc
#CFLAGS = -g -Wall

proj09: proj09.driver.c proj09.support.s /user/cse320/Projects/project09.support.h 
	gcc -Wall proj09.driver.c proj09.support.s /user/cse320/lib/reglib.o

clean:
	rm -f proj09.support.o
	rm -f proj09.driver.o
	rm -f proj09
