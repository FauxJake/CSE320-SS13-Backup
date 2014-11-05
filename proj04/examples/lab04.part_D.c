 
/****************************************************************************

  Lab Exercise #4 -- Part D

  Circuit which generates control signals to trigger four steps in sequence
  (Step 0, Step 1, Step 2, Step 3, Step 0, and so on).

  Current sequence of outputs:  1111, 0000, 0000, 0000, 0000, ....

  Desired sequence of outputs:  0001, 0010, 0100, 1000, 0001, ....

****************************************************************************/ 

#include <Sim.h>

void simnet()
{ 
  Signal Init;   // Signal to initialize sequencer to "1111"
  Signal Clk;    // Signal to synchronize flip-flops

  Signal Q0;     // Output of first flip-flop, trigger for Step 0
  Signal Q1;     // Trigger for Step 1
  Signal Q2;     // Trigger for Step 2
  Signal Q3;     // Trigger for Step 3

  // Pulsers to generate initialization signal and clock pulse

  Pulser ((SD("3a"), "i - Init"), Init, 'i', 1000);
  Pulser ((SD("4a"), "c - Clk" ), Clk,  'c', 1000);

  // Flip-flops to store state of sequencer

  Dff ((SD("2b"), "Dff3"), (Init, Zero, Clk, Zero), Q3);
  Dff ((SD("2c"), "Dff2"), (Init, Zero, Clk, Zero), Q2);
  Dff ((SD("2d"), "Dff1"), (Init, Zero, Clk, Zero), Q1);
  Dff ((SD("2e"), "Dff0"), (Init, Zero, Clk, Zero), Q0);

  // Probes to examine control signals issued by sequencer

  Probe ((SD("1b"), "Bit3"), Q3);
  Probe ((SD("1c"), "Bit2"), Q2);
  Probe ((SD("1d"), "Bit1"), Q1);
  Probe ((SD("1e"), "Bit0"), Q0);
}

