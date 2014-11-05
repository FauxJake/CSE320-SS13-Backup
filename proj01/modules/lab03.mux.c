
/*******************************************************************************
  Test bed for the Mux component

  The "Mux" component has the following characteristics:

    Select   (input)  -- N-bit control signal to select data signal
    Data-In  (input)  -- 2^N 1-bit data signals
    Data-Out (output) -- 1-bit data signal selected by control signals

*******************************************************************************/

#include <Sim.h>

void simnet()
{
  // Declare signals used in module
  //
  //   Signal name (num_bits, "label");

  Signal D2 (1, "Data signal 2");
  Signal D1 (1, "Data signal 1");
  Signal D0 (1, "Data signal 0");

  Signal C1 (1, "Control signal 1");
  Signal C0 (1, "Control signal 0");

  Signal MuxOut (1, "Mux Output");


  // Declare switches used to generate data and control signals
  //
  //   Switch (position, signal_out, key);

  Switch ((SD("1a"), "a -- Select bit 1"), C1, 'a');
  Switch ((SD("2a"), "b -- Select bit 0"), C0, 'b');

  Switch ((SD("4a"), "2 -- Data port 2"), D2, '2', One);
  Switch ((SD("5a"), "1 -- Data port 1"), D1, '1');
  Switch ((SD("6a"), "0 -- Data port 0"), D0, '0');


  // Declare 4-to-1 Mux
  //
  //   Mux (position, (select port), (data port), signal_out);

  Mux (SD("2b-4b"), (C1, C0), (One, D2, D1, D0), MuxOut);


  // Declare probe to examine Mux output
  //
  //   Probe (position, signal_in);

  Probe ((SD("3c"), "Mux Output"), MuxOut);
}

