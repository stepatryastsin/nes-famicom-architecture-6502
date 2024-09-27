#include "RAM.hpp"
#include "CPU.hpp"

RAM::RAM() {
    Init();
}
// Reads a 16 - bit word from RAM using the program counter(PC)
void RAM::Init() {
    memory.assign(MEM_SIZE, 0x00);
}
// Returns the memory value at the specified address (for constant objects).
uint16_t RAM::operator[](uint16_t address) const {
    if (address >= MEM_SIZE) {
        throw std::out_of_range("Address is out of bounds.");
    }
    return memory[address];
}

// Returns a reference to the memory value at the specified address (for non-constant objects).
uint16_t& RAM::operator[](uint16_t address) {
    return memory[address];
}
//Connects the RAM (RAM) to the CPU (CPU)
void RAM::ConnectCPU(std::shared_ptr<CPU> cpuPtr) {
    if (!cpuPtr) {
        throw std::invalid_argument("Invalid CPU pointer.");
    }
    cpu = std::move(cpuPtr);
}
