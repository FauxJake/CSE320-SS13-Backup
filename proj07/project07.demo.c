
#include <stdio.h>

#include "/user/cse320/Projects/project07.hardware.h"
#include "/user/cse320/Projects/project07.support.h"

/**************************************************************************
  Demonstrate how to use functions "read_reg_file" and "write_reg_file".

  Translation:
    gcc -Wall project07.driver.o project07.demo.c
**************************************************************************/ 

void execute()
{
  signal5 rd, rs1, rs2;
  signal32 RS1, RS2, RD;

  rs1 = 3;
  rs2 = 5;

  read_reg_file( rs1, rs2, &RS1, &RS2 );

  printf( "Inside execute -- rs1: %d  RS1: %08X\n\n", rs1, RS1 );
  printf( "Inside execute -- rs2: %d  RS2: %08X\n\n", rs2, RS2 );

  rd = 1;
  RD = 0x12345678;

  write_reg_file( rd, RD );
};

