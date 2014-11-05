
/******************************************************************************
  Test bed to experiment with the "Register" component

  The "Register" component has the following characteristics:

    Enable    -- enable signal
    Clk       -- clock pulse
    Input(s)  -- data input signal(s)
    Output(s) -- data output signal(s)

  The inputs are copied into the register (and become the outputs) whenever
  the enable signal is 1 and the leading edge of a clock pulse occurs.

  Standard usage:

    a) set data input signals to desired pattern
    b) assert enable signal
    c) wait for next clock pulse
    d) deassert enable signal
******************************************************************************/ 

#include <Sim.h>

void simnet()
{
  Signal Enable, Clk, D3, D2, D1, D0, Q3, Q2, Q1, Q0;

  // Keyboard mapping:
  //
  // e -- Enable signal
  // c -- Clock pulse
  //
  // 3 -- Most significant bit of four-bit input
  // 2
  // 1
  // 0 -- Least significant bit of four-bit input

  Switch ((SD("1a"), "e - Enable"), Enable, 'e');

  Pulser ((SD("1a"), "c - Clk"), Clk, 'c', 1000);
                      
  Space ("1a");

  Switch ((SD("1a"), "3 - D3"), D3, '3');
  Switch ((SD("1a"), "2 - D2"), D2, '2');
  Switch ((SD("1a"), "1 - D1"), D1, '1');
  Switch ((SD("1a"), "0 - D0"), D0, '0');

  Register (SD("1b"), Enable, Clk, (D3,D2,D1,D0), (Q3,Q2,Q1,Q0));

  Space (SD("1c"));
  Space (SD("1c"));
  Space (SD("1c"));

  Probe ((SD("1c"), "Q3"), Q3);
  Probe ((SD("1c"), "Q2"), Q2);
  Probe ((SD("1c"), "Q1"), Q1);
  Probe ((SD("1c"), "Q0"), Q0);
}

