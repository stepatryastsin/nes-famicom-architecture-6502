#include "RAM.hpp"
#include "CPU.hpp"

RAM::RAM() {
    Init();
}

void RAM::Init() {
    memory.resize(MEM_SIZE);
    std::fill(memory.begin(), memory.end(), 0x00);
}
//get
uint16_t RAM::operator[](uint16_t address) const {
    return memory[address];
}

//set
uint16_t& RAM::operator[](uint16_t address) {
    return memory[address];
}

void RAM::ConnectCPU(std::shared_ptr<CPU> cpuPtr) {
    cpu = std::move(cpuPtr); 
}
