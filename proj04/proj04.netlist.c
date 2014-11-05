/******************************************************************************
  Project #4
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal Init, Clock, w, x, y, z;

  Switch((SD("1a"), "i - init"), Init, 'i');
  Pulser((SD("2a"), "c - clock"), Clock, 'c', 1000);

  circuits( SD("1b-4b"), Init, Clock, w, x, y, z );

  Probe ((SD("1c"), "Bit0"), w);
  Probe ((SD("2c"), "Bit1"), x);
  Probe ((SD("3c"), "Bit2"), y);
  Probe ((SD("4c"), "Bit3"), z);
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal Init, Signal Clock, 
  Signal w, Signal x, Signal y, Signal z )
{
  Module( (sd, "circuits"), (Init, Clock), (w, x, y, z) );

  // Insert your declarations for any auxiliary Signals here
  Signal notw, notx, noty, notz;
  Signal W, X, Y, Z;
  

  // Insert your DFFs here
  Dff((SD(sd,"1e"), "Dff0"), (Init, W, Clock, Zero), w);
  Dff((SD(sd,"2e"), "Dff1"), (Zero, X, Clock, Zero), x);
  Dff((SD(sd,"3e"), "Dff2"), (Init, Y, Clock, Zero), y);
  Dff((SD(sd,"4e"), "Dff3"), (Zero, Z, Clock, Zero), z);

  // Insert your combinational logic here (Not, And, Or gates)
  Not(SD(sd,"2a"), w, notw);
  Not(SD(sd,"4a"), x, notx);
  Not(SD(sd,"6a"), y, noty);
  Not(SD(sd,"8a"), z, notz);

  //W(w,x,y,z) = w'yz'
  Or(SD(sd,"1c"), (x,y,notz), W);

  //X(w,x,y,z) = x' + y'z
  Signal Xand;

  And(SD(sd,"1b"),(noty,z), Xand);

  Or(SD(sd,"3c"),(Xand,notx), X);

  //Y(w,x,y,z) = xy' + xz' + x'z
  Signal Yand1, Yand2, Yand3;

  And(SD(sd,"3b"), (x,noty), Yand1);
  And(SD(sd,"4b"), (x,notz), Yand2);
  And(SD(sd,"5b"), (notx,z), Yand3);

  Or(SD(sd,"6c"), (Yand1, Yand2, Yand3), Y);

  //Z(w,x,y,z) = w'x' + y'z'
  Signal Zand1, Zand2;

  And(SD(sd,"7b"), (notw,notx), Zand1);
  And(SD(sd,"8b"), (noty,notz), Zand2);

  Or(SD(sd,"9c"), (Zand1,Zand2), Z);
  
}

