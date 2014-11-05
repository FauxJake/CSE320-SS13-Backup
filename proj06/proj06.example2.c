
#include <stdio.h>

/******************************************************************************
  Assume that a 64-bit unsigned integer data object contains a 48-bit
  signed integer object in bits 55 to 8.

  The program extracts and prints that 48-bit signed integer in three steps:

    a) Use a mask to extract the relevant 48 bits (bits 55 to 8).

    b) Shift the value to the left by 8 positions and copy it to a signed
	 data object.

    c) Shift the value to the right by 16 positions (with sign extension,
         since it is a signed data object).

  Note the use of the "%llx" and "%lld" formatting specs in the calls to
  "printf", as well as the "ULL" suffix on the 64-bit literal constants.
******************************************************************************/
 
int main()
{
  unsigned long long A[] = { 0x349056EF34CD7812ULL, 0x1234567890ABCDEFULL };
  unsigned long long B;
  signed long long C;
  int I, N;

  N = sizeof( A ) / sizeof( A[0] );

  for (I=0; I<N; I++)
  {
    B = A[I];

    //016llx = write a unsigned long long int in hexadecimal notation occupying a minimum of 16 positions, 
    //padded with 0.
    printf( "B before masking: %016llx\n", B ); 

    B = B & 0x00FFFFFFFFFFFF00ULL;

    printf( "B after masking:  %016llx\n", B );

    C = B << 8;

    printf( "C after shifting: %016llx\n", C );

    C = C >> 16;

    printf( "C after shifting: %016llx\n", C );

    printf( "C as a signed 64-bit integer: %+lld (base 10)\n\n", C );
  }

  return 0;
}
