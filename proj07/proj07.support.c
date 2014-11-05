/******************************************************************************
	Computer Project 07: The SPARC Instruction Set Architecture
	CSE320 SS13 - Jacob Riesser
******************************************************************************/

#include <stdio.h>
#include "/user/cse320/Projects/project07.hardware.h"
#include "/user/cse320/Projects/project07.support.h"


signal5 extract_op ( signal32 );
signal6 extract_op3 ( signal32 );
signal5 extract_rs1 ( signal32 );
signal5 extract_rs2 ( signal32 );
signal5 extract_rd ( signal32 );
signal13 get_simm13 ( signal32 );
signal1 extract_I ( signal32 );
void SRA ( signal5, signal5, signal5 );
void SRL ( signal5, signal5, signal5 );


/*-----------------------------------------------------------------------------
	Name: execute

	Purpose: simulate the actions of the CPU during the instruction
  			 fetch-execute cycle for the SPARC microprocessor.
-----------------------------------------------------------------------------*/
void execute()
{
	//IR and PSR are global so no worries
	unsigned long int op, op3, rs1, rs2, rd, I, simm13, carry;
	signal32 RS1, RS2;

	op = extract_op( IR );
	op3 = extract_op3( IR );
	I = extract_I( IR );
	rs1 = extract_rs1( IR );
	rd = extract_rd( IR );

	//printf("(BIN): %32s\n", bit32( IR ));
	//printf("op:    %2s\n", bit32(op) );
	//printf("op3:   %6s\n", bit32(op3) );
	//printf("I:     %1s\n", bit32(I) );
	//printf("rs1:   %5s\n", bit32(rs1) );
	//printf("rd:    %5s\n", bit32(rd) );

	

	//do actual calculations here
	//
	if (sizeof(IR) > 32) 
	{
		PSR ^= 1;
	}
	else
	{
		//sethi
		if ((int)op == 0)
		{
			signal32 RD, temp = 0, imm22;
			imm22 = IR & 0x003FFFFF;
			read_reg_file(rd, 0, &RD, &temp);
			RD = imm22;
			RD = RD << 10;
			write_reg_file(rd,RD);
		}
		else if ((int)op == 2)
		{
			if (rs1 > 32 || rs2 > 32) {PSR ^= 1; }//set exception bit (least sig bit in psr?)
			else{
				if (I == 1)
				{
					simm13 = get_simm13( IR );
					//printf("simm13:     %13s\n",bit32(simm13) );
					read_reg_file(rs1,0,&RS1,0); //only gets one value for RS1 and 0, since things have to grabbed in pairs
				}
				else 
				{
					rs2 = extract_rs2( IR );
					//printf("rs2:     %5s\n",bit32(rs2) );
					read_reg_file(rs1,rs2,&RS1,&RS2);
				}
				//printf("case 10 - arithmatic\n");
				switch ((int)op3)
				{
					//SHIFTING
					//
					case 0x27:
						//printf("SRA\n");
						if (I == 0) {SRA(rs1,rs2,rd);}
						else{PSR ^= 1;}
						break;
					case 0x26:
						//printf("SRL\n");
						if (I == 0) {SRL(rs1,rs2,rd);}
						else{PSR ^= 1;}
						break;
					case 0x25:
						//printf("SLL\n");
						RS1 = RS1 >> (int)RS2;
						write_reg_file(rd,RS1);
						break;

					//LOGICAL
					//
					case 0x7:
						//printf("XNOR\n");
						RS2 = ~RS2;
						if (I == 0)
						{
							RS1 = RS1 ^ RS2;
							write_reg_file(rd,RS1);
						}
						else if (I == 1)
						{
							RS1 = RS1 ^ simm13;
							write_reg_file(rd,RS1);
						}
						break;
					case 0x6:
						//printf("ORn\n");
						RS2 = ~RS2;
						if (I == 0)
						{
							RS1 = RS1 | RS2;
						}
						else if (I == 0)
						{
							RS1 = RS1 | simm13;
						}
						write_reg_file(rd,RS1);
						break;
					case 0x5:
						//printf("ANDn\n");
						RS2 = ~RS2;
						if (I == 0)
						{
							RS1 &= RS2;

						}
						else if (I == 1)
						{
							RS1 &=simm13;
						}

						write_reg_file(rd,RS1);
						break;
					case 0x3:
						//printf("XOR\n");
						if (I == 0)
						{
							RS1 = RS1 ^ RS2;
						}
						else if (I == 1)
						{
							RS1 = RS1 ^ simm13;
						}
						write_reg_file(rd,RS1);
						break;
					case 0x2:
						//printf("OR\n");
						if (I == 0)
						{
							RS1 = RS1 | RS2;
						}
						else if (I == 0)
						{
							RS1 = RS1 | simm13;
						}
						write_reg_file(rd,RS1);
						break;
					case 0x1:
						//printf("AND\n");
						if (I == 0)
						{
							RS1 &= RS2;
						}
						else if (I == 1)
						{
							RS1 &=simm13;
						}
						write_reg_file(rd,RS1);
						break;

					//ARITHMATIC
					//
					case 0xC:
						carry = (PSR & 0x100000) >> 20;
						if (I == 0){
							RS1 = RS1 - RS2 - carry;
						}
						else if (I == 1){
							RS1 = RS1 - simm13 - carry;
						}

						write_reg_file(rd,RS1);
						break;
					case 0x8:
						//printf("ADDx\n");
						carry = (PSR & 0x100000) >> 20;
						if (I == 0){
							RS1 = RS1 + RS2 + carry;
						}
						else if (I == 1){
							RS1 = RS1 + simm13 + carry;
						}

						write_reg_file(rd,RS1);
						break;
					case 0x4:
						//printf("SUB\n");
						if (I == 0){
							RS1 = RS1 - RS2;
						}
						else if (I == 1){
							RS1 = RS1 - simm13;
						}

						write_reg_file(rd,RS1);
						break;
					case 0x0:
						//printf("ADD\n");
						if (I == 0){
							RS1 = RS1 + RS2;
						}
						else if (I == 1){
							RS1 = RS1 + simm13;
						}

						write_reg_file(rd,RS1);
						break;
					default:
						//printf("INVALID\n");
						PSR ^= 1; //set exception bit (least sig bit in psr?)
						break;
				}
			}
		}
		else
		{
			//printf("INVALID OPERATION CODE\n");
			PSR ^= 1; //set exception bit (least sig bit in psr?)
		}
	}
}

/*-----------------------------------------------------------------------------
	HELPER FUNCTIONS

	Description: Helper functions to extract various bits of the IR and
				 clean up the code a bit.
-----------------------------------------------------------------------------*/

//EXTRACTION
signal5 extract_op ( signal32 instruction )
{
	return (instruction & 0xC0000000) >> 30;
}

signal6 extract_op3 ( signal32 instruction )
{
	return (instruction & 0x01f80000) >> 19;
}

signal5 extract_rs1 ( signal32 instruction )
{
	return (instruction & 0x0007E000ULL) >> 14;
}

signal5 extract_rs2 ( signal32 instruction )
{
	return (instruction & 0x0000001FULL);
}

signal5 extract_rd ( signal32 instruction )
{
	return (instruction & 0x3E000000ULL) >> 25;
}

signal1 extract_I ( signal32 instruction )
{
	return (instruction & 0x00002000ULL) >> 13;
}

signal13 get_simm13 ( signal32 instruction )
{
	return (instruction & 0x00001fffULL);
}

//INSTRUCTION FUNCTIONS
void SRA ( signal5 rs1, signal5 rs2, signal5 rd )
{
	//shift count is rs2
	//most sig bit of rs1 determines fill
	//output into rd

	unsigned sigBit, RS1, RS2, i, shftCnt = 0;
	sigBit = (rs1 & 0x10) >> 4;

	read_reg_file(rs1,rs2,&RS1,&RS2);

	if (sigBit == 1)
	{
		i=0;
		while (shftCnt < (int)RS2 && i <= 4)
		{
			RS1 = (RS2 << 1); //shift everything to the right 1
			RS1 |= (1 << 0); //set bit 0 to 1
			shftCnt++;
			i++;
		}
	}
	else
	{
		RS1 = RS1 << (int)RS2;
	}
	write_reg_file(rd, RS1);
}

void SRL ( signal5 rs1, signal5 rs2, signal5 rd )
{
	unsigned RS1,RS2; //values
	read_reg_file(rs1,rs1,&RS1,&RS2);
	RS1 = RS1 << (int)RS2;

	write_reg_file(rd,RS1);
}
