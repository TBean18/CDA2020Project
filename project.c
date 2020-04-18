/*
Taylor Bean, Quynh Lac Nguyen, John Pham
ta647999     qu404921          jo697580
4/05/2020

*/
#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    // if Add was selected or DONT CARE
    if  (ALUControl == 0b000)
    {
        *ALUresult = A + B;
    }
 
    // if SUB was selected
    // REMEMBER we are dealing with unsigned numbers, we need to account for overflow
    else if (ALUControl == 0b001)
    {
        *ALUresult =  A - B;
    }

    // If SLT is selected for SIGNED numbers
    else if (ALUControl == 0b010)
    {
        ((int)A < (int)B) ? (*ALUresult = 1) : (*ALUresult = 0);
    }

    // SLT has been selected for UNSIGNED Numbers
    else if (ALUControl == 0b011)
    {
        (A < B) ? (*ALUresult = 1) : (*ALUresult = 0);
    }
    // AND has been selected
    else if (ALUControl == 0b100)
    {
        *ALUresult = A & B;
    }

    // OR has been selected
    else if (ALUControl == 0b101)
    {
        *ALUresult = A | B;

    }
    // Left Shift 16 bits
    else if (ALUControl == 0b110)
    {
		*ALUresult = B << 16;
	}
    // Z = Negation of A
    else if (ALUControl == 0b111)
    {
        *ALUresult = ~A; 
    }
    //Asign Zero to 1 if the result is zero; otherwise, assign 0
    ((*ALUresult) == 0) ? (*Zero = 1) : (*Zero = 0);
    return;
}

/* instruction fetch */
/* 10 Points */
// Halt conditions for fetch are if the program counter is out of bounds of memory or if the program counter is not word-aligned, both of those should cause a halt
// And bounds for memory is 0x0 to 0xFFFF. Anything outside that halts.

int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // When it's not word aligned => halt
    if ((PC % 4) != 0) 
    {
        return 1;
    }
    // Otherwise, store the address at Mem[index] into instruction
    else
    {
        *instruction = Mem[PC >> 2]; 
    }
    return 0;
    
}


/* instruction partition */
/* 10 Points */
// Function is used to break up the command into its constituted parts (op, r1, r2, r3, funct, offset, jsec)
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{ 
    *op = (instruction & 0xFC000000) >> 26;     // instruction [31-26]
    *r1 = (instruction & 0x3E00000) >> 21;      // instruction [25-21]
    *r2 = (instruction & 0x1F0000) >> 16;       // instruction [20-16]
    *r3 = (instruction & 0xF800) >> 11;         // instruction [15-11]
    *funct = (instruction & 0x7F);         // instruction [5-0]
    *offset = instruction & 0xFFFF;      // instruction [15-0]
    *jsec = instruction & 0x3FFFFFF;     // instruction [25-0]
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op, struct_controls *controls)
{
    // Account for the halt conditions fall under default case

    // INITIALIZE all to zero and change needed singals in the swtich
    // Decode instruction using opcode
    controls->RegDst = 0;     // type R == 1, type I == 0
    controls->Jump = 0;       // 1 on Jump
    controls->Branch = 0;     // 1 on Branch
    controls->MemRead = 0;    // 
    controls->MemtoReg = 0;
    controls->ALUOp = 0;
    controls->MemWrite = 0;
    controls->ALUSrc = 1;     // type R == 0, type I and branching == 1
    controls->RegWrite = 0;

    // Look at OPcodes 
    switch (op)
    {
        // ALU will do addition or “don’t care”

    case 0: // ALL R-types have the same opCode of 000000 
        controls->RegDst = 1;
        controls->ALUOp = 7;
        controls->RegWrite = 1;
        controls->ALUSrc = 0;
        break;
        
    case 2: // Jump
        controls->RegDst = 2;
        controls->Jump = 1;
        controls->Branch = 2;
        controls->MemtoReg = 2;
        controls->ALUSrc = 2;

        break;

    case 4: // beq Selected
        controls->RegDst = 2;
        controls->Branch = 1;
        controls->MemtoReg = 2;
        controls->ALUOp = 1;
        controls->ALUSrc = 2;
        break;

    case 8: // addi Selected
        controls->RegWrite = 1;
        break;

    case 10: // slti Selected
        controls->ALUOp = 2;
        controls->RegWrite = 1;
        break;

    case 11: // sltiu Selected
        controls->ALUOp = 3;
        controls->RegWrite = 1;
        break;

    case 15: // Load Upper Immediate Selected
        controls->RegWrite = 1;
        controls->ALUOp = 6;
        break;
        
    case 35: // Load Word is Selected
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->RegWrite = 1;
        break;

    case 43: // SW is selected
        controls->MemWrite = 1;
        break;
    
    default: // Halt or someother error has occured
        return 1;
        break;
    }
    
    return 0;
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

    // If our MSB is 1 then we are NEGATIVE
    if ((offset >> 15) == 1)
    {
        //Since we are negative we must add 1's to the
        // MSB index
        // OR it with 16 1's, followed by 16 0's: extending our number with 1's
        *extended_value = offset + 0xFFFF0000;
        return;
    }
    else // We are positive
    {
        // Add 0's to the MSB
        // We do so by ANDing with 16 0's followed by 16 1's
        *extended_value = offset;
        return;
    }
       
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    // ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
    if (ALUOp == 7)
    {
        // If ALUOp is an R-type instruction, look at funct for further decoding
        switch (funct)
        {
            case 32:
                // Add
                ALUOp = 0;
                break;
            case 34:
                // Sub
                ALUOp = 1;
                break;
            case 36:
                // AND
                ALUOp = 4;
                break;
            case 37:
                // OR
                ALUOp = 5;
                break;
            case 42:
                // SLT 
                ALUOp = 2;
                break; 
            case 43:
                // Unsigned SLT
                ALUOp = 3;
                break;
            default: // Halt condition
                return 1;
                break;
        }
    }
    // if ALUOp is not valid => halt condition 
    else if (ALUOp > 7)
    {
        return 1;
    }

    
    // ALUSrc will determine whether or not we use data2 or extended_value as a parameter
    if (ALUSrc == 1)
    {
        ALU(data1, extended_value, ALUOp, ALUresult, Zero);
    }    
    else
    {
        ALU(data1, data2, ALUOp, ALUresult, Zero);
    }
    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    // Read memory
    if (MemRead == 1)
    {
        // ALU is an address, all words should be multiples of 4. Also check to see if ALUresult is
        // within bounds
        if ((ALUresult % 4) != 0 || ALUresult > 65535)
        {
            return 1;
        }
        // Store the address at the following index in memdata
        *memdata = Mem[ALUresult >> 2];
    } 
    // Write into memory
    else if (MemWrite == 1)
    {
        if ((ALUresult % 4) != 0 || ALUresult > 65535)
        {
            return 1;
        }
        // Store data2 in memory
        Mem[ALUresult >> 2] = data2;
    }
    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    if (RegWrite == 1) //Only write if we are told to
    {
        if (MemtoReg == 1) // Data is coming from memory
        {
            if (RegDst == 0)
            {
                Reg[r2] = memdata;
            }
        }
        else // data is coming from ALU-result
        {
            if (RegDst == 0)
            {
                Reg[r2] = ALUresult; 
            }
            else
            {
                Reg[r3] = ALUresult;
            }
        }
    } 
    
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    // Program counter is incremented by 4
    *PC += 4;
    // Left shift bits of jsec by 2 and use upper 4 bits of PC
    if (Jump == 1)
    {
       *PC = ((jsec << 2) + (*PC & 0xf0000000));
    }
    if (Zero == 1 && Branch == 1)
    {
        // Shift extended value by two and add it to PC
        *PC += (extended_value << 2);
    }
}
