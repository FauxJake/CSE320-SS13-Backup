/******************************************************************************
	Project 06: Floating Point Representation
	Driver File
******************************************************************************/

#include <stdio.h>
#include "/user/cse320/Projects/project06.support.h"
#include <assert.h>

//declarations so we can use custom functions
unsigned long long int extract_true_exp( const union dp_item );
unsigned long long int extract_exp( const union dp_item );
unsigned long long int extract_frac( const union dp_item );

int main()
{
	union dp_item A;
	unsigned long long int exponent, fraction;

	double Examples[] = { 5.25, 3, 79, 266754, -8, -5.75, 0 };

	int i;
	int N = sizeof(Examples)/sizeof(Examples[0]);

	printf("\nBEGIN PROGRAM\n/**********************************************************/\n\n");
	for ( i = 0; i < N; ++i)
	{
		A.drep = Examples[i];
		display(A.drep);
	}

	return 0;
}