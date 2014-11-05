 
/****************************************************************************

  Test bed to experiment with the "Dff" component

  The "Dff" component has four inputs:

    Set   -- Out becomes 1 when Set is asserted
    D     -- Out becomes D when Clk is asserted (on the rising edge)
    Clk   -- clock pulse
    Reset -- Out becomes 0 when Reset is asserted

  and one output:

    Out  -- current value stored in the flip-flop

  If you don't need to use a particular signal, give the constant signal
  "Zero" as its value.  For example, if the Set signal is not needed:

    Dff ("2b", (Zero, D, Clk, Reset), Out);

****************************************************************************/ 

#include <Sim.h>

void simnet()
{ 
  Signal Set, Reset, D, Clk, Out;

  // Keyboard mapping:
  //
  //   s -- Set signal (asynchronous)
  //   d -- Data signal
  //   c -- Clock signal
  //   r -- Reset signal (asynchronous)

  Switch ((SD("1a"), "s - Set"  ), Set,   's');
  Switch ((SD("2a"), "d - Data" ), D,     'd');
  Switch ((SD("3a"), "c - Clock"), Clk,   'c');
  Switch ((SD("4a"), "r - Reset"), Reset, 'r');

  Dff (SD("2b"), (Set, D, Clk, Reset), Out);

  Probe ((SD("2c"), "Dff-Out"), Out);
}

