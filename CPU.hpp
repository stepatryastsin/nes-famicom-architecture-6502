#ifndef CPU_H
#define CPU_H

#include "Opcode.hpp"
#include "RAM.hpp"
#include <memory>
#include <iostream>
#include <string>

class CPU {
public:
    uint8_t A = 0;
    uint8_t X = 0;
    uint8_t Y = 0;
    uint16_t PC = 0xFFFC;
    uint16_t SP = 0x00FF;


    struct Flags {
        bool C = false;  // Carry
        bool Z = false;  // Zero
        bool I = false;  // Interrupt Disable
        bool D = false;  // Decimal Mode
        bool B = false;  // Break Command
        bool V = false;  // Overflow
        bool N = false;  // Negative
    } flags;

  
    void connectRAM(std::shared_ptr<RAM> ramPtr);

  
    void reset();

    void step(uint8_t cycles);

private:
    std::shared_ptr<RAM> ram;

    uint8_t fetchByte(uint8_t& cycles);
    uint16_t fetchWord(uint8_t& cycles);
    void executeInstruction(uint8_t opcode, uint8_t& cycles);

    void setZeroFlag(uint8_t value);
    void setNegativeFlag(uint8_t value);


    // Write and read byte
    uint8_t rbyte(uint8_t& cycles,uint8_t addres);
    void wbyte(uint8_t& cycles, uint16_t byte, uint8_t addres);

    //Write and read two byte
    uint16_t r2byte(uint8_t& cycles, uint8_t addres);
    void w2byte(uint8_t& cycles,uint16_t byte2, uint8_t addres);
};

#endif // CPU_H