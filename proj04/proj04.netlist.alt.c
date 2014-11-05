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

  Pulser((SD("1a"), "i - init"), Init, 'i', 1000);
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
  //Signal NotW, NotX, NotY, NotZ;
  //Signal Q0, Q1, Q2, Q3, Q4, Q5;
  
  //Not(SD(sd,"1a"), W, NotW);
  //Not(SD(sd,"1a"), X, NotX);
  //Not(SD(sd,"1a"), Y, NotY);
  //Not(SD(sd,"1a"), Z, NotZ);
  
  //And(SD(sd,"1c"), (W, NotX, Y, NotZ), Q1);
  //And(SD(sd,"2c"), (NotW, X, NotY, NotZ), Q2);
  //And(SD(sd,"3c"), (NotW, NotX, Y, Z), Q3);
  //And(SD(sd,"4c"), (NotW, X, Y, Z), Q4);
  //And(SD(sd,"5c"), (NotW,NotX,NotY,NotZ), Q5);
  //And(SD(sd,"6c"), (NotW,X, Y, NotZ), Q0);
  

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

  //W(w,x,y,z) = x'yz
  Or(SD(sd,"1c"), (x,y,notz), W);

  //X(w,x,y,z) = wy + xy'z + x'yz + w'x'y'z'
  Signal Xand1, Xand2, Xand3, Xand4;

  And(SD(sd,"1b"),(noty,z), Xand1);
  And(SD(sd,"2b"), (x,noty), Xand2);
  And(SD(sd,"3b"), (x,notz), Xand3);
  And(SD(sd,"4b"), (notx,z), Xand4);
  
  Or(SD(sd,"3c"),(Xand1,Xand2,Xand3,Xand4), X);

  //Y(w,x,y,z) = x
  Signal Yand1, Yand2, Yand3;
  
  And(SD(sd,"4c"), (x, notx), Y);

  //Z(w,x,y,z) = w'y'z' + x'yz
  Signal Zand1, Zand2;

  And(SD(sd,"7b"), (notw,noty,notz), Zand1);
  And(SD(sd,"8b"), (notx,y,z), Zand2);

  Or(SD(sd,"9c"), (Zand1,Zand2), Z);
  
}

