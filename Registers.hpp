#ifndef REGISTERS_H
#define REGISTERS_H
enum class REGISTER {
	R_PC,             // 16 bit __ register Programm counter
	R_SP,             // 8  bit __ 256 byte stack located between $0100 & $01FF
	R_A ,             // 8  bit __ Accumulator 
	R_X ,             // 8  bit __ To hold counters or offsets for accessing memory
	R_Y ,             // 8  bit __ To hold counters or offsets for accessing memory
};

enum class PROCESSOR_STATUS{
	   CARRY_FLAG,    // __0__ Set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0
	    ZERO_FLAG,    // __1__ Set if the result of the last operation as was zero.
INTERRUPT_DISABLE,    // __2__ Set if the program has executed a 'Set Interrupt Disable' (SEI) instruction.
     DECIMAL_MODE,    // __3__ Set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction
    BREAK_COMMAND,    // __4__ Set when a BRK instruction has been executed and an interrupt has been generated to process it  
	          ONE,    // __5__ Set flag one
	OVERFLOW_FLAG,    // __6__ Set during arithmetic operations if the result has yielded an invalid 2's complement result
	NEGATIVE_FLAG,    // __7__ Set if the result of the last operation had bit 7 set to a one.
};
#endif // !REGISTERS_H
