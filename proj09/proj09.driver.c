/******************************************************************************
	Computer Project 09: SPARC Subprograms

	Jacob Riesser
	CSE320 SS13
******************************************************************************/

#include <stdio.h>

#include "/user/cse320/Projects/project09.support.h"

int main()
{
	int a,b,c;

	int count=5, i, j;

	b = 0;
	c = 0;

	printf("ADDITION/SUBTRACTION\n");
	for (i = 0; i < count; ++i)
	{
		a = add( b, c );
		printf("%08x + %08x = %08x\n",b,c,a );

		b += 1000;
		c += 876557;
	}

	a = 0;
	b = 0;
	c = 0;

	for (i = 0; i < count; ++i)
	{
		a = sub( b, c );
		printf("%08x - %08x = %08x\n",b,c,a );

		b += 150;
		c += 500;
	}

	printf("\nABSOLUTE/NEGATION\n");

	for (a = -2; a != count; ++a)
	{
		printf("a = %08x, -(a) = %08x, abs(a) = %08x\n", a, negate(a), absolute(a) );
	}

	printf("\nMULTIPLICATION/DIVISION/REMAINDER\n");

	for (i = 0; i < count; ++i)
	{
		a = mul( b, c );
		printf("%08x * %08x = %08x\n",b,c,a );

		b += 234;
		c += 23;
	}

	b = -345;
	c = 34;
	for (i=0; i < count; ++i)
	{
		a = divide( b, c );
		printf("%08x / %08x = %08x\n",b,c,a );

		b += 234;
		c += 23;
	}

	for (i=0; i < count; ++i)
	{
		a = remain( b, c );
		printf("%08x %% %08x = %08x\n",b,c,a );

		b += 234;
	}

	printf("\nFACTORIAL/POWER\n");
    b = 0;
	c = 0;
	for (i = -1; i < count; ++i)
	{
		printf("i = %08x i! = %08x\n",i, factorial(i));
	}

	j=0;
	for (i = -1; i < count; ++i)
	{
		printf("i = %08x, j = %08x, i^j = %08x\n",i, j, power(i,j));
		++j;
	}

	return 0;
}