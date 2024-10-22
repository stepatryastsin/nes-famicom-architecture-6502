#ifndef CHIP_H
#define CPUNES_H

#include <cstdint>
#include <memory>
#include <functional>
#include <bitset>
#include <optional>
#include <vector>
#include <string>
#include <array>

#define SIZERAM 65536 

class CHIP6502 {
public:
    CHIP6502();
    //Register
    uint8_t  a = 0x00;      // Accumulator Register
    uint8_t  x = 0x00;      // X Register
    uint8_t  y = 0x00;      // Y Register
    uint8_t  stkp = 0x00;   // Stack Pointer (on hardware stack)
    uint16_t pc = 0x0000;   // Program Counter

public:
    /*
      This is a variable that stores the current value fetched from
      memory for use in an arithmetic-logic unit (ALU).
      The value can be an operand for performing arithmetic
      operations (e.g. ADD, AND, etc.).
     */
     
    uint8_t  fetched = 0x00;

    /*This variable stores the absolute address that is used to access memory.
      This is the final address accessed by the processor when
      loading data or writing to memory.
     */

    uint16_t addr_abs = 0x0000;

    /*
     This is a variable that stores the relative address when making conditional jumps.
     This address is used when the instruction implies
     an offset from the current program position (e.g., when performing branching).
     */

    uint16_t addr_rel = 0x00;

    /*
     This is the current instruction that the processor is executing.
     It stores an instruction byte that specifies
     which operation to perform (e.g., LDA, ADC, JMP).
     */

    uint8_t  opcode = 0x00;

    /*
     This variable keeps track of the remaining number of cycles
     to execute the current instruction. When an instruction is executing,
     it may take several CPU cycles, and this variable
     allows you to track them until execution is complete.
     */

    uint8_t  cycles = 0;

     /*
     This is a global counter that increments with each clock cycle of the processor.
     It is used to keep track of the total number of clock cycles,
     which is important for measuring performance, tracking execution time,
     and synchronizing with other system components (e.g., for graphics updates).
     */

     uint32_t clock_count = 0;

public:
    // CPU flags
    enum class FLAG : uint8_t {
        C = 0, // Carry
        Z = 1, // Zero
        I = 2, // Interrupt Disable
        D = 3, // Decimal Mode
        B = 4, // Break Command
        U = 5, // Unused
        V = 6, // Overflow
        N = 7  // Negative
    };

public:
    //Reading and writing to the 6502 microchip memory
    uint8_t  read(uint16_t address) const;
    void     write(uint16_t address, uint8_t data);
    //Utility
    uint16_t readWord(uint16_t address);
    void     incrementPC(uint8_t amount = 1);
    uint16_t fetchWordFromPC();

public:
    //https://archive.org/details/rockwell_r650x_r651x (table instruction)

    struct Instruction {
        std::function<void()> operate;
        std::function<void()> addrMode;
        uint8_t cycles;
    };
    std::vector<Instruction> instruction;

public:
     //Controls system

    // Reset the CPU to a known initial state.
    // This is typically called when the system starts up or when the user
    // manually resets the CPU

    void reset();

    // Trigger an IRQ (Interrupt Request).
    // This is a maskable interrupt, meaning it can be disabled by clearing
    // the interrupt flag (I). This function simulates an external event
    // that generates an interrupt.

    void irq();

    // Trigger an NMI (Non-Maskable Interrupt).
    // This is a non-maskable interrupt, meaning it cannot be disabled.
    // It simulates an urgent event that needs immediate attention, such as
    // hardware failure or other critical situations.

    void nmi();

    // Clock the CPU.
    // Each call to this function processes a single CPU cycle. It's usually
    // called in a loop to simulate the continuous operation of the CPU
    // over time.

    void clock();


private:
    // Addressing modes(https://archive.org/details/rockwell_r650x_r651x)
    uint8_t IMP();
    uint8_t IMM();
    uint8_t ZP0();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t REL();
    uint8_t ABS();
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IND();
    uint8_t IZX();
    uint8_t IZY();

    // Opcodes
    uint8_t ADC();
    uint8_t AND();
    uint8_t ASL();
    uint8_t BCC();
    uint8_t BCS();
    uint8_t BEQ();
    uint8_t BIT();
    uint8_t BMI();
    uint8_t BNE();
    uint8_t BPL();
    uint8_t BRK();
    uint8_t BVC();
    uint8_t BVS();
    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
    uint8_t CLV();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();
    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();
    uint8_t EOR();
    uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t JMP();
    uint8_t JSR();
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t LSR();
    uint8_t NOP();
    uint8_t ORA();
    uint8_t PHA();
    uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();
    uint8_t ROL();
    uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();
    uint8_t SBC();
    uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();
    uint8_t TAX();
    uint8_t TAY();
    uint8_t TSX();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TYA();

	std::array<uint8_t, SIZERAM> ram{};
};

#endif