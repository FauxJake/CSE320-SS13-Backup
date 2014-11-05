/******************************************************************************
	Computer Project 5: Number Systems and Integer Representation

	conversion module source code file
******************************************************************************/

#include "/user/cse320/Projects/project05.support.h"
#include <stdlib.h>

void ReverseArray( int, char[] );

/*-----------------------------------------------------------------------------
	Name: ReverseArray

	Purpose: Reverses an array passed in as a pointer
	In:		n 	  -- number of elements in the array
			array -- the array, as a pointer
-----------------------------------------------------------------------------*/
void ReverseArray( int n, char* array)
{
	int end = n-1,ctr;
	char t;

	for (ctr = 0; ctr < n/2; ctr++) 
	{
	    t = array[ctr];
	    array[ctr] = array[end];
	    array[end] = t;
	 
	    end--;
	}
}

/*-----------------------------------------------------------------------------
	Name: convert

	purpose: Do the work required to convert a number to an external conversion
	In: 	N -- the number to convert (int)
			b -- the base to convert to (unsigned)
			C -- a pointer to an array in which the conversion will be stored
			f -- controls the formatting (0-append for negative, blank append for
				 positive)
	Out: 	Status -- either 1 for a successful conversion, or 0 for an
				      unsuccessful one
-----------------------------------------------------------------------------*/
int convert(int N, unsigned b, char* C, int f) 
{
	int Status = 1, s, end;
	char sign = (N >= 0) ? '+':'-';
	char dig, A[f];
	unsigned ctr=0;

	//CONVERSION BIT
	while(N != 0)
	{
		s = N % b;
		if (s>9){
			dig = (char)(((s-10)+'A'));
		}
		else{
			dig = (char)(((int)'0')+s);
		}
		A[ctr] = dig;
		N = N/b;
		ctr++;
	};
	
	//if f is too small, return 0 as described in handout
	if(ctr > abs(f)) 
	{ 
		return 0;
	}


	//CONVERSION DONE, BEGIN FORMATTING
	//formatting depending on f
	if (ctr == abs(f) -1) {A[ctr] = sign;}
	else if (f >=0)
	{
		A[ctr] = sign;
		ctr++;
		for (ctr;ctr<=f;ctr++)
		{
			A[ctr] = ' ';
		}
	}
	else
	{
		while (ctr < abs(f))
		{
			A[ctr] = (char)'0';
			ctr++;
		}
		ctr++;
		A[ctr] = sign;
			
	}
	
	//ctr is the index of digit as well as array, mark it as the end
	//of the first array for later concatenation
	end = ctr-1;
	
	//reverse the first array
	ReverseArray(end,A);
	
	//this is the base X part
	int Bsize;
	if (b > 9) {Bsize = 8;}
	else {Bsize = 7;}
	char B[Bsize];
	B[0] = ' ';
	B[1] = 'b';
	B[2] = 'a';
	B[3] = 's';
	B[4] = 'e';
	B[5] = ' ';
	
	if (b > 9)
	{	
		B[6] = ((int)b & 0xFF);
		B[7] = (((int)b >> 8) & 0xFF);
		B[8] = ' ';
	}
	else
	{
		B[6] = (b & 0xFF);
		B[7] = ' ';
	}
	
	//append two arrays into C to make desired format N base X
	int i1 = 0;
	int i2 = 0;
	
	while (i1<end)
	{
		C[i1] = A[i1];
		i1++;
	}
	
	while (i2 < 6)
	{
		C[i1] = B[i2];
		i1++;
		i2++;
	}
	
	return (int)Status;
}
