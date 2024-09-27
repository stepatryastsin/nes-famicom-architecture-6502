#include "CPU.hpp"

void CPU::ConnectRAM(std::shared_ptr<RAM> ramPtr) {
    _ram = ramPtr;
}

void CPU::ResetCPU() {
    PC = 0xFFFC;
    SP = 0x01FF; 
    A = X = Y = 0;
    flags = {};
}

void CPU::StepByInstruction(uint8_t cycles) {
    while (cycles > 0) {
        uint8_t opcode = FetchByte(cycles);
        ExecuteInstruction(opcode, cycles);
    }
}

uint8_t CPU::FetchByte(uint8_t& cycles) {
    if (!_ram) {
        throw std::runtime_error("RAM not connected!");
    }
    uint8_t byte = (*_ram)[PC];
    PC++;
    cycles--;
    return byte;
}

uint16_t CPU::FetchWord(uint8_t& cycles) {
    if (!_ram) {
        throw std::runtime_error("RAM not connected!");
    }

    uint16_t word = (*_ram)[PC];
    word |= ((*_ram)[PC] << 8);
    PC += 2;
    cycles -= 2; 
    return word;
}

void CPU::ExecuteInstruction(uint8_t opcode, uint8_t& cycles) {
    switch (opcode) {

    case LDA_IMIDEATE: {
        uint8_t value = FetchByte(cycles);
        A = value;
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_ZERO_PAGE: {
        uint8_t address = FetchByte(cycles);
        A = GetByte(cycles, address);
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_OFFSET_X: {
        uint8_t address = FetchByte(cycles) + X;
        A = GetByte(cycles, address);
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE: {
        uint16_t targetAddress = FetchWord(cycles);
        A = Get2Byte(cycles, targetAddress);
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE_X: {
        uint16_t TAddress = FetchWord(cycles);
        uint16_t OAdressX = TAddress + X;
        A = Get2Byte(cycles, OAdressX);
        if (OAdressX - TAddress >= 0xFF) {
            cycles--;
        }
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_ABSOLUTE_Y: {
        uint16_t TAddress = FetchWord(cycles);
        uint16_t OAdressY = TAddress + Y;
        A = Get2Byte(cycles, OAdressY);
        if (OAdressY - TAddress >= 0xFF) {
            cycles--;
        }
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_INDIRECT_X: {
        uint8_t ZPAddress = FetchByte(cycles) + X;
        cycles--; 
        uint16_t EFAddress = Get2Byte(cycles, ZPAddress);
        A = GetByte(cycles, EFAddress);
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }
    case LDA_INDIRECT_Y: {
        uint8_t ZPAddress = FetchByte(cycles);
        uint16_t EFAddress = Get2Byte(cycles, ZPAddress);
        uint16_t OAdressY = EFAddress + Y;
        cycles--;
        A = GetByte(cycles, EFAddress);
        if (OAdressY - EFAddress >= 0xFF) {
            cycles--;
        }
        SetZeroFlag(A);
        SetNegativeFlag(A);
        break;
    }

    case JSR_ABSOLUTE: {
        uint16_t targetAddress = FetchWord(cycles);
        Set2Byte(cycles, PC - 1, 0x0100 + SP);
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

void CPU::SetZeroFlag(uint8_t value) {
    flags.Z = (value == 0);
}

void CPU::SetNegativeFlag(uint8_t value) {
    flags.N = (value & 0x80) != 0;  
}

uint8_t CPU::GetByte(uint8_t& cycles, uint16_t address) {
    uint8_t byte = (*_ram)[address];  
    cycles--;
    return byte;
}

void CPU::SetByte(uint8_t& cycles, uint8_t value, uint16_t address) {
    (*_ram)[address] = value;
    cycles--;
}

uint16_t CPU::Get2Byte(uint8_t& cycles, uint16_t address) {
    uint16_t word = (*_ram)[address];
    word |= ((*_ram)[address + 1] << 8);
    cycles -= 2;
    return word;
}

void CPU::Set2Byte(uint8_t& cycles, uint16_t word, uint16_t address) {
    (*_ram)[address] = word & 0xFF;
    (*_ram)[address + 1] = (word >> 8);
    cycles -= 2;
}
