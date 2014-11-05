
#ifndef HARDWARE_
#define HARDWARE_

/**************************************************************************
  Instructor-supplied data types, data objects, and functions
**************************************************************************/

typedef unsigned signal1;
typedef unsigned signal2;
typedef unsigned signal3;
typedef unsigned signal5;
typedef unsigned signal6;
typedef unsigned signal13;
typedef unsigned signal22;
typedef unsigned signal32;

/*-------------------------------------------------------------------------
  The control registers.
-------------------------------------------------------------------------*/

extern signal32 IR, PSR;

/*-------------------------------------------------------------------------
  Function:  read_reg_file

  Purpose:   Fetch the contents of two registers from the register file.
    RS1 output port <== Reg[RS1 selection signal]
    RS2 output port <== Reg[RS2 selection signal]
-------------------------------------------------------------------------*/

void read_reg_file
(
  signal5,    /* RS1 selection signal */
  signal5,    /* RS2 selection signal */
  signal32*,  /* RS1 output port      */
  signal32*   /* RS2 output port      */
);

/*-------------------------------------------------------------------------
  Function:  write_reg_file

  Purpose:   Update the contents of one register in the register file.
    Reg[RD selection signal] <== RD input port
-------------------------------------------------------------------------*/

void write_reg_file
(
  signal5,    /* RD selection signal  */
  signal32    /* RD input port        */
);

#endif

