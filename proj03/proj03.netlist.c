/******************************************************************************
  Project #3 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
  Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal w, x, y, z, Present, a, b, c, d, e, f, g;
  Signal Strobe (1);   // Counter strobe input
  Signal ResetA (1);   // Counter reset signal (before complemented)
  Signal ResetB (1);   // Counter reset signal (after complemented)
  Signal Output (4);

  Pulser ((SD("aa"), "r -- Reset counter"),  ResetA, 'r', 10000);
  Pulser ((SD("ba"), "s -- Strobe counter"), Strobe, 's', 10000);

  Not (SD("ab"), ResetA, ResetB);

  // Code to generate four input signals
  Counter ((SD("ac-bc"), "4-bit counter"), (ResetB, Strobe), (w,x,y,z));
  

  // Code to display eight output signals
  circuits( SD("ae-de"), w, x, y, z, Present, a, b, c, d, e, f, g);

  Probe(SD("ai", "Present"), Present);
  Probe(SD("ag", "a"), a);
  Probe(SD("bh", "b"), b);
  Probe(SD("dh", "c"), c);
  Probe(SD("eg", "d"), d);
  Probe(SD("df", "e"), e);
  Probe(SD("bf", "f"), f);
  Probe(SD("cg", "g"), g);
}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Present, Signal a, Signal b, Signal c, Signal d, Signal e,
  Signal f, Signal g )    
{
  Module( (sd, "circuits"), (w, x, y, z), (Present, a, b, c, d, e, f, g) );

  // Declarations for any auxiliary Signals
  Signal notw, notx, noty, notz;
  Signal and1, and2, and3, and4;
  Signal Band1, Band2;
  Signal Dand1, Dand2, Dand3;
  Signal Eand1, Eand2;

  // Circuit implementation (Not, And, Or gates)

  //Present w'x + w'y'z' + w'yz + wx'yz'
  Not(SD(sd,"ab"), w, notw);
  Not(SD(sd,"ad"), x, notx);
  Not(SD(sd,"af"), y, noty);
  Not(SD(sd,"ah"), z, notz);

  And(SD(sd,"ba"), (notw, x), and1);                      //w'x
  And(SD(sd,"bb"), (notw, noty, notz), and2);             //w'y'z'
  And(SD(sd,"bc"), (notw, y, z), and3);                   //w'yz
  And(SD(sd,"bd"), (w, notx, y, notz), and4);             //wx'yz'

  Or(SD(sd,"ca"), (and1, and2, and3, and4), Present);

  //A x' + y + z
  Or(SD(sd,"cb"), (notx, y, z), a);                       //x' + y + z

  //B y'z' + yz + x'+y'z' + yz
  And(SD(sd,"be"), (noty, notz), Band1);                   //y'z'
  And(SD(sd,"bf"), (y,z), Band2);                          //yz        
  Or(SD(sd,"cc"), (notx,Band1,Band2), b);                    //x' + y'z' + yz

  //C y = z'
  Or(SD(sd,"ce"), (y, notz), c);                          //y + z'

  //D w'x' + y'z + w'yz'
  And(SD(sd,"bg"), (notw,notx), Dand1);                     //w'x'
  And(SD(sd,"bh"), (noty, z), Dand2);                       //y'z
  And(SD(sd,"bi"), (notw,y,notz), Dand3);                   //w'yz'

  Or(SD(sd,"cf"), (Dand1,Dand2,Dand3), d);                    

  //E yz' + x'y'
  And(SD(sd,"bj"), (y, notz), Eand1);                       //yz'
  And(SD(sd,"bh"), (notx,noty), Eand2);                     //x'y'

  Or(SD(sd,"cg"), (Eand1,Eand2), e);                         

  //F y' + z'
  Or(SD(sd,"ci"), (noty,notz), f);

  //G x' + y' + z'
  Or(SD(sd,"cj"),(notx,noty,notz), g);
}

