#include "CPU.hpp"

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//    Copyright (c) 2024 Stepa Tryastsin                                   //
//                                                                         //
//    Follow along on GitHub:  https://github.com/stepatryastsin           //
//    The source code in this project is licensed under the MIT license.   //
//                                                                         //
//    Description:                                                         //
//    A study project to dive into the topic of emulating processors,      //
//    architectures, and graphical mapping through the NES.                //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
//                                                    //
//                       Public                       //
//                                                    //
////////////////////////////////////////////////////////

//Attaches RAM (RAM) to the processor (CPU).

void CPU::ConnectRAM(std::shared_ptr<RAM> ramPtr) {
    _ram = std::move(ramPtr);
    if (!_ram) {
        throw std::runtime_error("RAM not connected!");
    }
}
// Resets the processor, setting the register and stack pointer values to defaults.

void CPU::ResetCPU() {
    PC = 0xFFFC;
    SP = 0x01FF; 
    A = X = Y = 0;
    flags = {};
}
// Executes an instruction by receiving an operation code and executing the corresponding function.
void CPU::StepByInstruction(uint8_t cycles) {
    if (cycles < 0) {
        throw std::runtime_error("The cycles are too short !");
    }
    while (cycles > 0){
      uint8_t opcode = FetchByte(cycles);
      ExecuteInstruction(opcode, cycles);
    } 
   
}

////////////////////////////////////////////////////////
//                                                    //
//                     Private                        //
//                                                    //
////////////////////////////////////////////////////////


//Interprets and executes the opcode instruction. Lambda function is used to load data into registers
void CPU::ExecuteInstruction(uint8_t opcode, uint8_t& cycles) {
    auto LoadCurrentRegister = [&](uint16_t address, uint8_t& r) {
        r = GetByte(cycles, address);
        LoadRegisterStatus(r);
    };
    switch (opcode) {
///////////////////////////////////LDA/////////////////////////////////////////////
    case LDA_IMIDEATE: {
        A = FetchByte(cycles);
        LoadRegisterStatus(A);
        break;
    }
    case LDA_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        LoadCurrentRegister(address,A);
        break;
    }
    case LDA_ZERO_PAGE_OFFSET_X: {
        uint8_t address = AddrZeroPageX(cycles);
        LoadCurrentRegister(address, A);
        break;
    }
    case LDA_ABSOLUTE: {
        uint16_t address = AddrAbsolute(cycles);
        LoadCurrentRegister(address,A);
        break;
    }
    case LDA_ABSOLUTE_OFFSET_X: {
        uint16_t address = AddrAbsoluteX(cycles);
        LoadCurrentRegister(address, A);
        break;
    }
    case LDA_ABSOLUTE_OFFSET_Y: {
        uint16_t address = AddrAbsoluteY(cycles);
        LoadCurrentRegister(address, A);
        break;
    }
    case LDA_INDIRECT_OFFSET_X: {
        uint16_t Address = Get2Byte(cycles, FetchByte(cycles));
        uint16_t AdressX = Address + X;
        cycles--;
        A = GetByte(cycles, AdressX);
        LoadRegisterStatus(A);
        break;
    }
    case LDA_INDIRECT_OFFSET_Y: {
        uint16_t Address = Get2Byte(cycles, FetchByte(cycles));
        uint16_t AdressY = Address + X;
        cycles = ValidateMemoryPageBoundaries(Address, AdressY) ? cycles-- : cycles;
        cycles--;
        A = GetByte(cycles, AdressY);
        LoadRegisterStatus(A);
        break;
    }
//////////////////////////////////LDA/////////////////////////////////////////////////

//////////////////////////////////LDX/////////////////////////////////////////////////
    case LDX_IMIDEATE: {
        X = FetchByte(cycles);
        LoadRegisterStatus(X);
        break;
    }
    case LDX_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        LoadCurrentRegister(address, X);
        break;
    }
    case LDX_ABSOLUTE: {
        uint16_t address = AddrAbsolute(cycles);
        LoadCurrentRegister(address,X);
        break;
    }
    case LDX_ZERO_PAGE_OFFSET_Y: {
        uint8_t address = AddrZeroPageY(cycles);
        LoadCurrentRegister(address, X);
        break;
    }
    case LDX_ABSOLUTE_OFFSET_Y: {
        uint16_t address = AddrAbsoluteY(cycles);
        LoadCurrentRegister(address, A);
        break;
    }

//////////////////////////////////LDX/////////////////////////////////////////////////

//////////////////////////////////LDY/////////////////////////////////////////////////
    case LDY_IMIDEATE: {
        X = FetchByte(cycles);
        LoadRegisterStatus(X);
        break;
    }
    case LDY_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        LoadCurrentRegister(address, X);
        break;
    }
    case LDY_ZERO_PAGE_OFFSET_X: {
        uint8_t address = AddrZeroPageX(cycles);
        LoadCurrentRegister(address, Y);
        break;
    }
    case LDY_ABSOLUTE: {
        uint16_t address = AddrAbsolute(cycles);
        LoadCurrentRegister(address, Y);
        break;
    }

    case LDY_ABSOLUTE_OFFSET_X: {
        uint16_t address = AddrAbsoluteX(cycles);
        LoadCurrentRegister(address, Y);
        break;
    }

//////////////////////////////////LDY/////////////////////////////////////////////////

//////////////////////////////////STA/////////////////////////////////////////////////

    case STA_ABSOLUTE:{
        uint16_t address = AddrAbsolute(cycles);
        SetByte(cycles, A,address);
        break;
    }
    case STA_ABSOLUTE_OFFSET_X: {
        uint16_t address = AddrAbsoluteX(cycles);
        SetByte(cycles, A, address);
        break;
    }
    case STA_ABSOLUTE_OFFSET_Y: {
        uint16_t address = AddrAbsoluteY(cycles);
        SetByte(cycles, A, address);
        break;
    }
    case STA_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        SetByte(cycles, A, address);
        break;
    }
    case STA_ZERO_PAGE_OFFSET_X: {
        uint16_t address = AddrZeroPageX(cycles);
        SetByte(cycles, A, address);
        break;
    }
    case STA_INDIRECT_OFFSET_X: {
        //need test 
        uint16_t address = AddrAbsoluteX(cycles);
        Set2Byte(cycles, A, address);
        cycles--;
        break;
    }
    case STA_INDIRECT_OFFSET_Y: {
        //need test 
        uint16_t address = AddrAbsoluteY(cycles);
        Set2Byte(cycles, A, address);
        cycles--;
        break;
    }
//////////////////////////////////STA/////////////////////////////////////////////////

//////////////////////////////////STX/////////////////////////////////////////////////
    case STX_ABSOLUTE: {
        uint16_t address = AddrAbsolute(cycles);
        SetByte(cycles, X, address);
        break;
    }
    case STX_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        SetByte(cycles, X, address);
        break;
    }
    case STX_ZERO_PAGE_OFFSET_Y: {
        uint16_t address = AddrZeroPageY(cycles);
        SetByte(cycles, X, address);
        break;
    }
//////////////////////////////////STX/////////////////////////////////////////////////

//////////////////////////////////STX/////////////////////////////////////////////////
    case STY_ABSOLUTE: {
        uint16_t address = AddrAbsolute(cycles);
        SetByte(cycles, Y, address);
        break;
    }
    case STY_ZERO_PAGE: {
        uint16_t address = AddrZeroPage(cycles);
        SetByte(cycles, Y, address);
        break;
    }
    case STY_ZERO_PAGE_OFFSET_X: {
        uint16_t address = AddrZeroPageX(cycles);
        SetByte(cycles, Y, address);
        break;
    }
//////////////////////////////////STX/////////////////////////////////////////////////

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
//Sets the register flags by checking the zero and negative states.
void CPU::LoadRegisterStatus(uint8_t Register)
{
  SetZeroFlag(Register);
  SetNegativeFlag(Register);
}
// Returns a 16-bit address from memory page zero
uint16_t CPU::AddrZeroPage(uint8_t& Cycles)
{
    uint8_t address = FetchByte(Cycles);
    if (address > 0xFF) {
        throw std::runtime_error("Overflow of the first memory page!");
    }
    return address;
}
// Returns a 16-bit address from memory page zero with offset X
uint16_t CPU::AddrZeroPageX(uint8_t& Cycles)
{
    uint8_t address = FetchByte(Cycles) + X;
    if (address > 0xFF) {
        throw std::runtime_error("Overflow of the first memory page!");
    }
    Cycles--;
    return address;
}
// Returns a 16-bit address from memory page zero with offset Y
uint16_t CPU::AddrZeroPageY(uint8_t& Cycles)
{
    uint8_t address = FetchByte(Cycles) + Y;
    if (address > 0xFF) {
        throw std::runtime_error("Overflow of the first memory page!");
    }
    Cycles--;
    return address;
}
//Returns the absolute address
uint16_t CPU::AddrAbsolute(uint8_t& Cycles)
{
    uint16_t address = FetchWord(Cycles);
    return address;
}
//Returns the absolute address with an X offset added. If the offset crosses a page boundary, loops are decremented.
uint16_t CPU::AddrAbsoluteX(uint8_t& Cycles)
{
    uint16_t Address = FetchWord(Cycles);
    uint16_t AdressX = Address + X;
    Cycles = ValidateMemoryPageBoundaries(Address, AdressX) ? Cycles-- : Cycles;
    return AdressX;
}
//Returns the absolute address with an Y offset added. If the offset crosses a page boundary, loops are decremented.
uint16_t CPU::AddrAbsoluteY(uint8_t& Cycles)
{
    uint16_t Address = FetchWord(Cycles);
    uint16_t AdressX = Address + Y;
    Cycles = ValidateMemoryPageBoundaries(Address, AdressX) ? Cycles-- : Cycles;
    return AdressX;
}

void CPU::SetZeroFlag(uint8_t value) {
    flags.Z = (value == 0);
}

void CPU::SetNegativeFlag(uint8_t value) {
    flags.N = (value & 0x80) != 0;
}

//Reads a byte from RAM at an address.
uint8_t CPU::GetByte(uint8_t& cycles, uint16_t address) {
    uint8_t byte = (*_ram)[address];
    if (CheckValidMemory(byte)) {
        throw new std::runtime_error("Out of the range of allowed RAM memory");
    }
    cycles--;
    return (*_ram)[address];
}

//Write a byte from RAM at an address.
void CPU::SetByte(uint8_t& cycles, uint8_t value, uint16_t address) {
    (*_ram)[address] = value;
    cycles--;
}

//Reads a 2 byte from RAM at an address.
uint16_t CPU::Get2Byte(uint8_t& cycles, uint16_t address) {
    uint16_t word = (*_ram)[address];
    word |= ((*_ram)[address + 1] << 8);
    if (CheckValidMemory(word)) {
        throw new std::runtime_error("Out of the range of allowed RAM memory");
    }
    cycles -= 2;
    return word;
}

//Write a 2 byte from RAM at an address.
void CPU::Set2Byte(uint8_t& cycles, uint16_t word, uint16_t address) {
    (*_ram)[address] = word & 0xFF;
    (*_ram)[address + 1] = (word >> 8);
    cycles -= 2;
}

//Reads a 8-bit word from RAM using the program counter (PC)
uint8_t CPU::FetchByte(uint8_t& cycles) {
    if (!_ram) {
        throw std::runtime_error("RAM not connected!");
    }
    uint8_t byte = (*_ram)[PC];
    if (CheckValidMemory(byte)) {
        throw new std::runtime_error("Out of the range of allowed RAM memory");
    }
    PC++;
    cycles--;
    return byte;
}

//Reads a 16-bit word from RAM using the program counter (PC)
uint16_t CPU::FetchWord(uint8_t& cycles) {
    if (!_ram) {
        throw std::runtime_error("RAM not connected!");
    }

    uint16_t word = (*_ram)[PC];
    word |= ((*_ram)[PC] << 8);
    if (CheckValidMemory(word)) {
        throw new std::runtime_error("Out of the range of allowed RAM memory");
    }
    PC += 2;
    cycles -= 2;
    return word;
}

bool CPU::ValidateMemoryPageBoundaries(uint16_t& Faddress, uint16_t& Saddress)
{
    if (Saddress - Faddress >= 0xFF) {
        return true;
    }
    return false;
}

bool CPU::CheckValidMemory(uint16_t address)
{
    if (address < 0x0000 || address > 0xFFFF) {
        return true;
    }
    return false;
}

void CPU::PushStack(uint8_t& Cycles) {
    Set2Byte(Cycles,PC-1,SPTAddress());
    SP -= 2;
}


uint16_t CPU::PopStack(uint8_t& Cycles) {
    uint16_t val = Get2Byte(Cycles, SPTAddress() + 1);
    Cycles--;
    SP += 2;
    return val;
}