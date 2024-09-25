#include <iostream>
#include <memory>
#include "CPU.hpp"
#include "RAM.hpp"

int main(int argc, char* argv[]) {

    auto ram = std::make_shared<RAM>();
    auto cpu = std::make_shared<CPU>();

  
    cpu->connectRAM(ram);

    cpu->reset();


    (*ram)[0xFFFC] = LDA_ZERO_PAGE;   
    (*ram)[0xFFFD] = 0x42;  
    (*ram)[0x0042] = 0x84;

    cpu->step(3);

    std::cout << "A: " << std::hex << static_cast<int>(cpu->A) << std::endl;

    return 0;
}
