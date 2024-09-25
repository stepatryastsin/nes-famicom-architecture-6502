#include "CPU.hpp"

void CPU::connectRAM(std::shared_ptr<RAM> ramPtr) {
    ram = ramPtr;
}

void CPU::reset() {
    PC = 0xFFFC;
    SP = 0x00FF;
    A = X = Y = 0;

    // ׁבנמס פכאדמג
    flags = {};
}

void CPU::step(uint8_t cycles) {
    while (cycles > 0) {
        uint8_t opcode = fetchByte(cycles);
        executeInstruction(opcode, cycles);
    }
}

uint8_t CPU::fetchByte(uint8_t& cycles) {
    if (!ram) {
        throw std::runtime_error("RAM not connected!");
    }

    uint8_t byte = (*ram)[PC];
    PC++;
    cycles--;
    return byte;
}

uint16_t CPU::fetchWord(uint8_t& cycles)
{
    if (!ram) {
        throw std::runtime_error("RAM not connected!");
    }
    uint16_t byte_2 = (*ram)[PC];
    PC++;
    cycles--;

    byte_2 |= ((*ram)[PC] << 8);
    PC++;
    cycles--;
    return byte_2;
}

void CPU::executeInstruction(uint8_t opcode, uint8_t& cycles) {
    switch (opcode) {
    case LDA_IMIDEATE: {
        uint8_t targetAddress = fetchByte(cycles);
        A = targetAddress;
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_ZERO_PAGE: {
        uint8_t targetAddress = fetchByte(cycles);
        A = rbyte(cycles , targetAddress);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_OFFSET_X: {
        uint8_t targetAddress = fetchByte(cycles);
        targetAddress += X;
        cycles--;
        A = rbyte(cycles, targetAddress);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case JSR_ABSOLUTE: {

        uint16_t targetAddress = fetchWord(cycles);
        w2byte(cycles, PC - 1, SP);
        SP -= 2;
        PC = targetAddress;
        cycles--;
    }
    default:
        std::cout << "Debug information: unknown opcode " << static_cast<int>(opcode) << "\n";
        break;
    }
}


void CPU::setZeroFlag(uint8_t value) {

    flags.Z = (value == 0);

}


void CPU::setNegativeFlag(uint8_t value) {

    flags.N = (value & 0x80) != 0;  

}

uint8_t CPU::rbyte(uint8_t& cycles, uint8_t addres)
{
    uint8_t byte = (*ram)[addres];
    cycles--;
    return byte;
}

void CPU::wbyte(uint8_t& cycles, uint16_t byte, uint8_t addres)
{

    (*ram)[addres] = (byte & 0xFF);
    cycles--;

}


uint16_t CPU::r2byte(uint8_t& cycles, uint8_t addres)
{

    uint16_t byte2 = (*ram)[addres];
    cycles--;

    byte2 |= ((*ram)[addres + 1] << 8);
    cycles--;
    return byte2;

}

void CPU::w2byte(uint8_t& cycles,uint16_t byte2, uint8_t addres)
{

    (*ram)[addres] = byte2 & 0xFF;
    (*ram)[addres + 1] = (byte2 >> 8) & 0xFF;
    cycles -= 2;

}
