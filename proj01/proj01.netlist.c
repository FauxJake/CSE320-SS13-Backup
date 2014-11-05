/******************************************************************************
  Project 01
  Jacob Riesser
  A43730576
******************************************************************************/

#include <Sim.h> 

/*-----------------------------------------------------------------------------
  Function "circuits" -- implementation of student circuits
-----------------------------------------------------------------------------*/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Valid, Signal Present, Signal Even, Signal Prime )    
{
    Module( (sd, "circuits"), (w, x, y, z), (Valid, Present, Even, Prime) );
    
    Signal notw, notx, noty, notz;
    
    // Valid(w,x,y,z) = w' + xy' + x'yz
    Signal and1, and2, and3;
    
    Not(SD(sd,"a1"), w, notw);
    Not(SD(sd,"a2"), x, notx);
    Not(SD(sd,"a3"), y, noty);
    Not(SD(sd,"a4"), z, notz);

    And(SD(sd,"b1"), (notw, notw), and1);                   //w'
    And(SD(sd,"b2"), (w, notx, noty), and2);                //x'y'
    And(SD(sd,"b3"), (w, notx, y, notz), and3);             //x'yz
          
    Or(SD(sd,"c2"), (and1, and2, and3), Valid);
    
    //Present(w,x,y,z) = w'x + w'x'z' + w'yz + wx'yz'
    //
    Signal Pnotw, Pnotx, Pnoty, Pnotz;
    Signal Pand1, Pand2, Pand3, Pand4;
    
    
    And(SD(sd,"b4"), (notw, x), Pand1);                     //w'x
    And(SD(sd,"b5"), (notw, noty, notz), Pand2);            //w'x'z'
    And(SD(sd,"b6"), (notw, y, z), Pand3);                  //w'yz
    And(SD(sd,"b7"), (w, notx, y, notz), Pand4);            //wx'yz'
    
    Or(SD(sd,"c3"), (Pand1, Pand2, Pand3, Pand4), Present);
    
    //Even(w,x,y,z) = y'z' + yz'
    //
    Signal Eand1, Eand2;
    
    And(SD(sd,"b8"), (noty, notz, Present), Eand1);         //y'z'     
    And(SD(sd,"b9"), (y, notz, Present), Eand2);            //yz'
    
    Or(SD(sd, "c5"), (Eand1, Eand2), Even);
    
    //Prime(w,x,y,z) = w'z
    //
    And(SD(sd,"c1"), (notw, z, Present), Prime);            //w'z
}



/*----------------------------------------------------------------------------*
  Function "simnet"   -- test bed for student circuits
-----------------------------------------------------------------------------*/

void simnet()
{
  Signal w, x, y, z, Valid, Present, Even, Prime;

  // Insert your Switches here
  Switch( SD("1a"), w, 'w');
  Switch( SD("2a"), x, 'x');
  Switch( SD("3a"), y, 'y');
  Switch( SD("4a"), z, 'z');

  circuits( SD("1b-4b"), w, x, y, z, Valid, Present, Even, Prime );

  // Insert your Probes here
  Probe(SD("1c", "Valid"), Valid);
  Probe(SD("2c", "Present"), Present);
  Probe(SD("3c", "Even"), Even);
  Probe(SD("4c", "Prime"), Prime);
}




