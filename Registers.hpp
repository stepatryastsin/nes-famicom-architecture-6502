#ifndef REGISTERS_H
#define REGISTERS_H

enum class REGISTER {
	R_PC = 0x0000,             // 16 bit __ register Programm counter
	R_SP   = 0x00,             // 8  bit __ 256 byte stack located between $0100 & $01FF
	R_A    = 0x00,             // 8  bit __ Accumulator 
	R_X    = 0x00,             // 8  bit __ To hold counters or offsets for accessing memory
	R_Y    = 0x00,             // 8  bit __ To hold counters or offsets for accessing memory
};

enum class FLAG{
	    CARRY_FLAG = (1 << 0),    // __0__Ñ__ Set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0
	     ZERO_FLAG = (1 << 1),    // __1__Z__ Set if the result of the last operation as was zero.
    INTERRUPT_FLAG = (1 << 2),    // __2__I__ Set if the program has executed a 'Set Interrupt Disable' (SEI) instruction.
      DECIMAL_FLAG = (1 << 3),    // __3__D__ Set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction
        BREAK_FLAG = (1 << 4),    // __4__B__ Set when a BRK instruction has been executed and an interrupt has been generated to process it  
	      ONE_FLAG = (1 << 5),    // __5__0__ Set flag one(unused)
	 OVERFLOW_FLAG = (1 << 6),    // __6__V__ Set during arithmetic operations if the result has yielded an invalid 2's complement result
	 NEGATIVE_FLAG = (1 << 7),    // __7__N__ Set if the result of the last operation had bit 7 set to a one.
};


#endif // !REGISTERS_H
