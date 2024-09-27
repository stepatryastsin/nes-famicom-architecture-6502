#include <iostream>
#include <memory>
#include "CPU.hpp"
#include "RAM.hpp"

int main(int argc, char* argv[]) {

    auto ram = std::make_shared<RAM>();
    auto cpu = std::make_shared<CPU>();
    cpu->ConnectRAM(ram);
    cpu->ResetCPU();
    cpu->X = 0x02;  

    (*ram)[0xFFFC] = JSR_ABSOLUTE;  
    (*ram)[0xFFFD] = 0x42;
    (*ram)[0xFFFE] = 0x42;
    (*ram)[0x4242] = LDA_OFFSET_X;  
    (*ram)[0x4243] = 0x01;         
    (*ram)[0x4244] = 0x67;         

    (*ram)[0x0003] = 0x99;         

    cpu->StepByInstruction(9); 

    if (cpu->A == 0x99) {
        std::cout << "LDA_OFFSET_X  A: " << static_cast<int>(cpu->A) << std::endl;
    }
    else {
        std::cout << "Error LDA_OFFSET_X.  " << static_cast<int>(cpu->A) << std::endl;
    }
}
