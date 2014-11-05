#Makefile for proj05
#
proj05: proj05.support.o proj05.driver.o
	gcc -o proj05 proj05.support.o	proj05.driver.o

driver.o: proj05.driver.c
	gcc -c proj05.driver.c

support.o: proj05.support.c /user/cse320/Projects/project05.support.h
	gcc -c proj05.support.c 

clean:
	rm -f proj05.driver.o proj05.support.o
