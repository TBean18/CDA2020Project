#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    // Ask Prof. how the ALUControl is passed to the ALU function

    unsigned ALUControlBinary;
    // int ASCIIVal = (int)ALUControl;

    //Convert char ALUControl into Binary
    ALUControlBinary = (int)(ALUControl);

    // if Add was selected or DONT CARE
    if  (ALUControlBinary == 000){
        *ALUresult = A + B;

    }
 
    // if SUB was selected
    // REMEMBER we are dealing with unsigned numbers, we need to account for overflow
    else if (ALUControlBinary == 001)
    {
        *ALUresult =  A - B;
    }

    // If SLT is selected for SIGNED numbers
    else if (ALUControlBinary == 010)
    {
        (A < B) ? (*ALUresult = 1) : (*ALUresult = 0);

    }

    // SLT has been selected for UNSIGNED Numbers
    else if(ALUControlBinary == 011)
    {
        (A < B) ? (*ALUresult = 1) : (*ALUresult = 0);


    }
    // AND has been selected
    else if(ALUControlBinary == 100)
    {
        *ALUresult = A & B;
        
    }

    // OR has been selected
    else if(ALUControlBinary == 101)
    {
        *ALUresult = A | B;

    }
    // Left Shift 16 bits
    else if(ALUControlBinary == 110)
    {
		B = B << 4;
	}
    // Z = Negation of A
    else if(ALUControlBinary == 111)
    {
        *ALUresult = ~A; 
    }
    //Asign Zero to 1 if the result is zero; otherwise, assign 0
    ((*ALUresult) == 0) ? (*Zero = '1') : (*Zero = '0');
    return;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    *instruction = Mem[PC >> 2];

    if (*instruction == // Whatever it takes to halt)
    {
        return 1;
    }
    return 0;
    
}


/* instruction partition */
/* 10 Points */
// Function is used to break up the command into its constituted parts (op, r1, r2, r3, funct, offset, jsec)
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    

    *op = (instruction & 0xFC000000) >> 26; // instruction [31-26]
    *r1 = (instruction & 0x3E00000) >> 21; // instruction [25-21]
    *r2 = (instruction & 0x1F0000) >> 16;// instruction [20-16]
    *r3 = (instruction & 0xE000) >> 11;// instruction [15-11]
    *funct = (instruction & 0x3F) >> 0;// instruction [5-0]
    *offset = (instruction & 0xFFFF) >> 0;// instruction [15-0]
    *jsec = (instruction & 0x3FFFFFF) >> 0;// instruction [25-0]

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    switch (op)
    {
        //ALU will do addition or “don’t care”
    case 000:
        /* code */
        break;
    case 001:
        /* code */
        break;
    case 010:
        /* code */
        break;
    case 011:
        /* code */
        break;
    
    default:
        break;
    }
    // Decode instruction using opcode
    controls->RegDst;
    controls->Jump;
    controls->Branch;
    controls->MemRead;
    controls->MemtoReg;
    controls->ALUOp;
    controls->MemWrite;
    controls->ALUSrc;
    controls->RegWrite;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // Giving and i type number that's going into offset, b/c of this,
    // it was never in a register before, so we take the number and 
    // extend it into a 32 bit binary value.


    
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    // ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
    if (ALUsrc)
    ALU(data1, data2, )
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

// Personally created function for assigning the zero value
void assignZero(unsigned *ALUresult,char *Zero)
{

}
