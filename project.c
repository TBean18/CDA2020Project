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
        *ALUresult = A + B;;

        // Check for result == 0
       
        (*ALUresult) == (unsigned)0 ? *Zero = 1 : *Zero = 0;
        return;

    }
 
    // if SUB was selected
    // REMEMBER we are dealing with unsigned numbers, we need to account for overflow
    else if (ALUControlBinary == 001){
        Z =
        *ALUresult =  A - B;
        A < B ? Z = 1 : Z = 0;        return;
    }

    // If SLT is selected for signed numbers
    else if (ALUControlBinary == 010){
        A < B ? *ALUresult = 1 : *ALUresult = 0;
        }

    // SLT has been selected for Signed Numbers
    else if(ALUControlBinary == 011){

    }
    // AND has been selected
    else if(ALUControlBinary == 100){

    }

    // OR has been selected
    else if(ALUControlBinary == 101){

    }
    // Left Shift 16 bits
    else if(ALUControlBinary == 110){

    }
    // Z = Negation of A
    else if(ALUControlBinary == 111){

    }
    //Asign Zero to 1 if the result is zero; otherwise, assign 0
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* instruction partition */
/* 10 Points */
// Function is used to break up the command into its constituted parts (op, r1, r2, r3, funct, offset, jsec)
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

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
void assignZero(unsigned *ALUresult,char *Zero){

}
