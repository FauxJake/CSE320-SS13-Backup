
/*******************************************************************************

  Test bed for the Decoder component

  The "Decoder" component has the following characteristics:

    Enable   (input)  -- enable decoder (active high)
    Data-In  (input)  -- N-bit data value
    Data-Out (output) -- decoded data value (2^N signals, only one asserted)

  The "Counter" component has the following characteristics:

    Reset  (input)  -- reset counter to zero (active low)
    Strobe (input)  -- output the next value in the count sequence
    Data   (output) -- current value in the count sequence

*******************************************************************************/

#include <Sim.h>

void simnet()
{
  // Declare signals used in module
  //
  //   Signal name (num_bits);

  Signal Strobe (1);   // Counter strobe input
  Signal ResetA (1);   // Counter reset signal (before complemented)
  Signal ResetB (1);   // Counter reset signal (after complemented)

  Signal Enable (1);   // Decoder enable input
  Signal Data   (3);   // Decoder data input (3 bits)
  Signal Output (8);   // Decoder data output (8 bits)

  // Switch used to generate the enable signal for the decoder

  Switch ((SD("1a"), "e -- Enable decoder"), Enable, 'e');

  // A pulser is used to generate a temporary value of "One" on a specified
  // signal line (signal value:  Zero ==> One ==> Zero)

  Pulser ((SD("3a"), "r -- Reset counter"),  ResetA, 'r', 10000);
  Pulser ((SD("4a"), "s -- Strobe counter"), Strobe, 's', 10000);

  // Complement the reset signal (counter reset is active low)

  Not (SD("3b"), ResetA, ResetB);

  Counter ((SD("3c-4c"), "3-bit counter"), (ResetB, Strobe), Data);

  Decoder ((SD("1d-4d"), "3-to-8 decoder"), Enable, Data, Output);
  
  Probe ((SD("1e-4e"), "Output"), Output);
}

