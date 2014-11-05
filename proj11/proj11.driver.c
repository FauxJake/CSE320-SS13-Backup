/******************************************************************************
	COMPUTER PROJECT 11 (FINAL PROJECT): SPARC FLOATING POINT OPERATIONS
	DRIVER MODULE

	JACOB RIESSER
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double absolute( double );
double modulo( double, double );
double factorial( unsigned );
double power( double, unsigned );
double sine( double );

union dp_item
{
  double drep;
  unsigned long long int irep;
};

int main()
{
	double A,B;
	unsigned i,j, count = 6;

	union dp_item spec_INF, spec_NAN;

	spec_INF.irep = 0x7ff00000;
	spec_NAN.irep = 0x7ff00001;

	/*
		TEST ABSOLUTE
	*/
	for (i = 0; i < count; ++i)
	{
		B = rand() % 100 + 1;
		if (i & 1)
		{
			B *= -1;
		}
		A = absolute(B);
		printf("absolute(%16.8lf) = %16.8lf\n", B,A);
	}

	printf("SPECIAL CASES\n");
	printf("absolute(INF) = %16.8lf\n",absolute(spec_INF.drep) );
	printf("absolute(NAN) = %16.8lf\n",absolute(spec_NAN.drep) );

	/*
		TEST MODULO
	*/
	A = -2;
	B = -3;
	for (i = 0; i < count; ++i)
	{
		printf("modulo(%16.8lf, %16.8lf) = %16.8lf\n",A,B,modulo(A,B));
		printf("fmod  (%16.8lf, %16.8lf) = %16.8lf\n",A,B,fmod(A,B));
		A+=3456;
		B+=3;
	}
	printf("SPECIAL CASES\n");
	printf("modulo(INF, 2.00) = %16.8lf\n",modulo(spec_INF.drep,2.00) );
	printf("fmod(INF, 2.00)   = %16.8lf\n",fmod(spec_INF.drep,2.00) );
	printf("modulo(NAN, 2.00) = %16.8lf\n",modulo(spec_NAN.drep,2.00) );
	printf("fmod(NAN, 2.00)   = %16.8lf\n",fmod(spec_NAN.drep,2.00) );

	/*
		TEST POWER
	*/
	A = -2;
	B = -1;
	for (i = 0; i < count; ++i)
	{
		printf("power(%16.8lf, %16.8lf) = %16.8lf\n",A,B,power(A,B) );
		
		A+=2;
		B+=1;
	}
	printf("SPECIAL CASES\n");
	printf("power(INF, 2.00) = %16.8lf\n",power(spec_INF.drep,2.00) );
	printf("pow(INF, 2.00)   = %16.8lf\n",pow(spec_INF.drep,2.00) );
	printf("power(NAN, 2.00) = %16.8lf\n",power(spec_NAN.drep,2.00) );
	printf("pow(NAN, 2.00)   = %16.8lf\n",pow(spec_NAN.drep,2.00) );

	/*
		TEST FACTORIAL
	*/
	j = 0;
	for ( i = 0; i < count; ++i)
	{
		printf("factorial(%i) = %16.8lf\n",j,factorial(j));
		j++;
	}
	printf("SPECIAL CASES\n");
	printf("factorial(INF) = %16.8lf\n",factorial(spec_INF.drep) );
	printf("factorial(NAN) = %16.8lf\n",factorial(spec_NAN.drep) );

	/*
		TEST SINE
	*/
	A = M_PI;
	for (i = 0; i < count; ++i)
	{
		printf("sine(%16.8lf) = %16.8lf\nsin(%16.8lf)  = %16.8lf\n", A, sine(A), A, sin(A) );
		A += 3*M_PI;
	}
	printf("SPECIAL CASES\n");
	printf("sine(INF) = %16.8lf\n",sine(spec_INF.drep) );
	printf("sin(INF)  = %16.8lf\n",sin(spec_INF.drep) );
	printf("sine(NAN) = %16.8lf\n",sine(spec_NAN.drep) );
	printf("sin(NAN)  = %16.8lf\n",sin(spec_NAN.drep) );

	return 0;
}