/******************************************************************************
	Project 05: Number Systems and Integer Representation
	
	Driver Module
******************************************************************************/

#include <stdio.h>

int main()
{
	int I, count, A=45, f=5,status,n=30;
	unsigned b = 16;
	char bar[26] = "-------------------------\0";
	
	char C[30];
	
	status = convert(A,b,C,f);

	printf("\nCoverting +45 to Base 16\n%s\nCode: %i",bar,status);
	
	
	printf("\nConvert values\n'");
	for (count=0; count < n; count++)
	{
		printf("%c", C[count]);
	}
	printf("'\n");
	
	f = -5;
	status = convert(A,b,C,f);
	printf("\nWith a negative 'f' value\n%s\nCode: %i",bar,status);
	printf("\nConvert values\n'");
	for (count=0; count < n; count++)
	{
		printf("%c", C[count]);
	}
	printf("'\n");
	
	return 0;
}

