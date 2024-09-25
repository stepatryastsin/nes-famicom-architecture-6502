#include "RAM.hpp"
#include "CPU.hpp"

RAM::RAM() {
    init();
}

void RAM::init() {
    mem.resize(MEM_SIZE);
    for (size_t i = 0; i < MEM_SIZE; i++)
    {
        mem[i] = 0x00;
    }
}

uint16_t RAM::operator[](uint16_t address) const {
    return mem[address];
}


uint16_t& RAM::operator[](uint16_t address) {
    return mem[address];
}

void RAM::connectCPU(std::shared_ptr<CPU> cpuPtr) {
    cpu = std::move(cpuPtr); 
}
