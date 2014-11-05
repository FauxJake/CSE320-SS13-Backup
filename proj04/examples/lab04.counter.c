
/*******************************************************************************

  Test bed for the Counter component

  The "Counter" component has the following characteristics:

    Reset  (input)  -- reset counter to zero (active low)
    Strobe (input)  -- output the next value in the count sequence
    Data   (output) -- current value in the count sequence

*******************************************************************************/

#include <Sim.h>

void simnet()
{
  Signal Strobe (1);   // Counter strobe input
  Signal ResetA (1);   // Counter reset signal (before complemented)
  Signal ResetB (1);   // Counter reset signal (after complemented)
  Signal Output (4);   // Counter output

  // A pulser is used to generate a temporary value of "One" on a specified
  // signal line (signal value:  Zero ==> One ==> Zero)

  Pulser ((SD("1a"), "r -- Reset counter"),  ResetA, 'r', 10000);
  Pulser ((SD("2a"), "s -- Strobe counter"), Strobe, 's', 10000);

  // Complement the reset signal (counter reset is active low)

  Not (SD("1b"), ResetA, ResetB);

  Counter ((SD("1c-2c"), "4-bit counter"), (ResetB, Strobe), Output);

  Probe ((SD("1d-2d"), "Output"), Output);
}

