/******************************************************************************
	Computer Project 6: Floating Point Representation
	Supporting file
******************************************************************************/

#include <stdio.h>
#include <assert.h> //testing only! remove!
#include "/user/cse320/Projects/project06.support.h"

unsigned long long int extract_true_exp( const union dp_item );
unsigned long long int extract_exp( const union dp_item );
unsigned long long int extract_frac( const union dp_item );

/*-----------------------------------------------------------------------------
	Name: extract_exp

	purpose: returns the exponent for the fp representation
-----------------------------------------------------------------------------*/
unsigned long long int extract_frac( const union dp_item A)
{
	return (A.irep & 0x000fffffffffffffULL);
}
/*-----------------------------------------------------------------------------
	Name: extract_exp / extract_true_exp

	purpose: returns the exponent for the fp representation, with and w/o bias
-----------------------------------------------------------------------------*/
unsigned long long int extract_exp( const union dp_item A)
{
	if (A.irep == 0) {return 0;}
	return ((A.irep & 0x7ff0000000000000ULL) >> 52);
}

unsigned long long int extract_true_exp( const union dp_item A)
{
	return (extract_exp(A) == 0) ? 0:extract_exp(A) - 0x03ff;
}
/*-----------------------------------------------------------------------------
	Name: is_negative

	purpose: checks for negativity of a double value
-----------------------------------------------------------------------------*/
int is_negative( double A )
{
	union dp_item B;
	B.drep = A;

	unsigned long long int sign_bit_mask = 0x8000000000000000ULL;
	if ((B.irep & sign_bit_mask) == 0x0000000000000000ULL) {return 1;}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: is_zero

	purpose: Test if argument is zero
-----------------------------------------------------------------------------*/
int is_zero( double A )
{
	union dp_item B;
	B.drep = A;

	//exponent fields and significand are both all 0's => +0 or -0
	if ((extract_exp(B) == 0) && (extract_frac(B) == 0))
	{
		return 1;
	}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: is_denormal

	purpose: Test if argument is denormal
	condition: exponent of all 0's
-----------------------------------------------------------------------------*/
int is_denormal( double A )
{
	union dp_item B;
	B.drep = A;

	if (extract_exp(B) == 0){return 1;}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: is_nan

	purpose: Test if argument is NaN
	condition: exponent of all 1's, and a fraction (last 52 bits) that IS NOT
			   all 0's
-----------------------------------------------------------------------------*/
int is_nan( double A )
{
	union dp_item B;

	B.drep = A;

	if (extract_exp(B) == 0x7ff0000000000000ULL && extract_frac(B) != 0)
	{
		return 1;
	}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: is_infinite

	purpose: Test if argument is INF
	condition: exponent of all 1's and an fraction (last 52 bits) of all 0's
-----------------------------------------------------------------------------*/
int is_infinite( double A )
{
	union dp_item B;
	unsigned long long int mask = 0x7ff0000000000000ULL;

	B.drep = A;

	if ((B.irep & mask) == 0x7ff0000000000000ULL){return 1;}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: is_finite

	purpose: Test if argument is finite
	condition: as long as the number is not infinte right?
-----------------------------------------------------------------------------*/
int is_finite( double A )
{
	if (!is_infinite(A)) {return 1;}
	return 0;
}

/*-----------------------------------------------------------------------------
	Name: negate

	purpose: returns negation of argument
-----------------------------------------------------------------------------*/
double negate( double A )
{
	union dp_item B, temp;
	B.drep = A;
	B.irep ^= (1 << 63);

	return B.drep;
}

/*-----------------------------------------------------------------------------
	Name: absolute

	purpose: return absolute value of argument (flip the sign bit)
-----------------------------------------------------------------------------*/
double absolute( double A )
{
	union dp_item B;
	B.drep = A;

	if (is_negative(A))
	{
		//toggles most significant bit, i.e.: the sign bit
		B.drep = negate(B.drep);
	}

	return B.drep;
}

/*-----------------------------------------------------------------------------
	Name: display

	purpose: display the fields of the argument in float 64 form
-----------------------------------------------------------------------------*/
void display( double A )
{
	int i;
	unsigned long long int biased_exp, true_exp;

	const char *status;
	const char *status_code[5];
	status_code[0] = "normal";
	status_code[1] = "infinity";
	status_code[2] = "not-a-number";
	status_code[3] = "zero";
	status_code[4] = "denormal";

	union dp_item B;
	B.drep = A;
	biased_exp = extract_exp(B);
	true_exp = extract_true_exp(B);
	//significand schtuff here

	//select a status code. 'most specific' to 'least specific' special conditions,
	//otherwise, normal is default
	status = 
		is_zero(A) == 1 ? status_code[3]
		: is_denormal(A) == 1 ? status_code[4]
		: is_infinite(A) == 1 ? status_code[1]
		: is_nan(A) == 1 ? status_code[2]
		: status_code[0];

	printf("****************************************\n");
	printf("Number:               0x%016llx [%+f (base 10)]\n\n",A,A );
	printf("a. Biased Exponenent: 0x%016llx [%+lld (base 10)]\n",biased_exp, biased_exp );
	printf("b. True Exponenent:   0x%016llx [%+lld (base 10)]\n",true_exp, true_exp );
	printf("c. Significand:       \n");
	printf("d. Status:            %s\n", status );

	//test negation and absolute
	B.drep = absolute(A);
	printf("Absolute value of A:  0x%016llx [%+d (base10)]\n", B.drep, B.drep );
	B.drep = negate(A);
	printf("Negation of A:        0x%016llx [%+d (base10)]\n\n", B.drep, B.drep );
    printf("----------------------------------------\n\n");
}