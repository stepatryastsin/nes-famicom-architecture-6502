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

public:

    void ConnectRAM(std::shared_ptr<RAM> ramPtr);

    void ResetCPU();

    void StepByInstruction(uint8_t cycles) ;

private:

    std::shared_ptr<RAM> _ram;

    uint8_t FetchByte(uint8_t& cycles);

    uint16_t FetchWord(uint8_t& cycles);

    void ExecuteInstruction(uint8_t opcode, uint8_t& cycles);

    void SetZeroFlag(uint8_t value);

    void SetNegativeFlag(uint8_t value);


private:

    // Write and read byte
    uint8_t GetByte(uint8_t& cycles, uint16_t address);

    void SetByte(uint8_t& cycles, uint8_t value, uint16_t address);

    //Write and read two byte
    uint16_t Get2Byte(uint8_t& cycles, uint16_t address);

    void Set2Byte(uint8_t& cycles, uint16_t word, uint16_t address);

private:

    void LoadRegisterStatus(uint8_t Register);

    //Adresing mode//
    uint16_t AddrZeroPage(uint8_t& Cycles);

    /** Zero page with X offset */
    uint16_t AddrZeroPageX(uint8_t& Cycles);

    /**Zero page with Y offset */
    uint16_t AddrZeroPageY(uint8_t& Cycles);

    /** Absolute */
    uint16_t AddrAbsolute(uint8_t& Cycles);

    /**Absolute with X offset */
    uint16_t AddrAbsoluteX(uint8_t& Cycles);

    /** Absolute with Y offset */
    uint16_t AddrAbsoluteY(uint8_t& Cycles);


   bool ValidateMemoryPageBoundaries(uint16_t& Faddress, uint16_t& Saddress);

   bool CheckValidMemory(uint16_t address);
};

#endif // CPU_H