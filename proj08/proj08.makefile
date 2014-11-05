#makefile for project 08

proj08: proj08.student.s
	gcc -Wall proj08.student.s /user/cse320/lib/reglib.o
