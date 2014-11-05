
/*******************************************************************************
  Demonstrate the use of hierarchical modules

  The "Mux421" component represents a bank of four 2-to-1 multiplexers; it has
  two 4-bit data inputs and one 4-bit data output.  The control signal maps
  one of the data inputs to the data output.

  The "Mux421" component has the following characteristics:

    Select   (input)  -- 1-bit control signal to select data signal
    Data-InA (input)  -- 4-bit data signal on Port 1
    Data-InB (input)  -- 4-bit data signal on Port 0
    Data-Out (output) -- 4-bit data signal selected by control signal

*******************************************************************************/

#include <Sim.h>

void Mux421 (const SD& sd, const Signal& In, const Signal& Out)
{
  Module ((sd,"Mux421"), In, Out);

  Signal Select = (In[8]);
  Signal InA = (In[7]-In[4]);
  Signal InB = (In[3]-In[0]);

  Mux (SD(sd,"1a"), (Select), (InA[3], InB[3]), Out[3]);
  Mux (SD(sd,"2a"), (Select), (InA[2], InB[2]), Out[2]);
  Mux (SD(sd,"3a"), (Select), (InA[1], InB[1]), Out[1]);
  Mux (SD(sd,"4a"), (Select), (InA[0], InB[0]), Out[0]);
}

void simnet()
{
  Sig (Select, 1);
  Sig (ItemA, 4);
  Sig (ItemB, 4);
  Sig (MuxOut, 4);

  Switch (SD("1a"), Select, 's');
  Space (SD("2a"));
  Switch (SD("3a-4a"), ItemA, 'a');
  Space (SD("5a"));
  Switch (SD("6a-7a"), ItemB, '1');

  Mux421 (SD("2b-4b"), (Select, ItemA, ItemB), MuxOut);

  Probe (SD("2c-4c"), MuxOut);
}

