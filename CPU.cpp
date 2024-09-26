#include "CPU.hpp"

void CPU::connectRAM(std::shared_ptr<RAM> ramPtr) {
    ram = ramPtr;
}

void CPU::reset() {
    PC = 0xFFFC;
    SP = 0x00FF;  // Стек начинается с 0x01FF, SP указывает на 8-битное значение
    A = X = Y = 0;

    // Сброс флагов
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

uint16_t CPU::fetchWord(uint8_t& cycles) {
    if (!ram) {
        throw std::runtime_error("RAM not connected!");
    }

    uint16_t word = (*ram)[PC];
    PC++;
    word |= ((*ram)[PC] << 8);
    PC++;
    cycles -= 2; 
    return word;
}

void CPU::executeInstruction(uint8_t opcode, uint8_t& cycles) {
    switch (opcode) {

    case LDA_IMIDEATE: {
        uint8_t value = fetchByte(cycles);
        A = value;
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_ZERO_PAGE: {
        uint8_t address = fetchByte(cycles);
        A = rbyte(cycles, address);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_OFFSET_X: {
        uint8_t address = fetchByte(cycles);
        address += X;  
        A = rbyte(cycles, address);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE: {
        uint16_t targetAddress = fetchWord(cycles);
        A = r2byte(cycles, targetAddress);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE_X: {
        uint16_t targetAddress = fetchWord(cycles);
        uint16_t offsetAdressX = targetAddress + X;
        A = r2byte(cycles, offsetAdressX);
        if (offsetAdressX - targetAddress >= 0xFF) {
            cycles--;
        }
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE_Y: {
        uint16_t targetAddress = fetchWord(cycles);
        uint16_t offsetAdressY = targetAddress + Y;
        A = r2byte(cycles, offsetAdressY);
        if (offsetAdressY - targetAddress >= 0xFF) {
            cycles--;
        }
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_INDIRECT_X: {
        uint8_t zeroPageAddr = fetchByte(cycles);
        zeroPageAddr += X;
        cycles--; 
        uint16_t effectiveAddr = r2byte(cycles, zeroPageAddr);
        A = rbyte(cycles, effectiveAddr);
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }
    case LDA_INDIRECT_Y: {
        uint8_t zeroPageAddr = fetchByte(cycles);
        uint16_t effectiveAddr = r2byte(cycles, zeroPageAddr);
        uint16_t adressOffsetY = effectiveAddr + Y;
        cycles--;
        A = rbyte(cycles, effectiveAddr);
        if (adressOffsetY - effectiveAddr >= 0xFF) {
            cycles--;
        }
        setZeroFlag(A);
        setNegativeFlag(A);
        break;
    }

    case JSR_ABSOLUTE: {
        uint16_t targetAddress = fetchWord(cycles);
        w2byte(cycles, PC - 1, 0x0100 + SP);
        SP -= 2;  
        PC = targetAddress; 
        cycles -= 1;
        break;
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

uint8_t CPU::rbyte(uint8_t& cycles, uint16_t address) {
    uint8_t byte = (*ram)[address];  
    cycles--;
    return byte;
}

void CPU::wbyte(uint8_t& cycles, uint8_t value, uint16_t address) {
    (*ram)[address] = value;
    cycles--;
}

uint16_t CPU::r2byte(uint8_t& cycles, uint16_t address) {
    uint16_t word = (*ram)[address];
    word |= ((*ram)[address + 1] << 8);
    cycles -= 2;
    return word;
}

void CPU::w2byte(uint8_t& cycles, uint16_t word, uint16_t address) {
    (*ram)[address] = word & 0xFF;
    (*ram)[address + 1] = (word >> 8);
    cycles -= 2;
}
