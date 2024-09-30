
#include "CPU.hpp"
#include "RAM.hpp"
#include <iostream>
#include <memory>


void LoadTestProgram(std::shared_ptr<RAM> ram) {

    (*ram)[0xFFFC] = LDA_IMIDEATE; 
    (*ram)[0xFFFD] = 0x42;        
    (*ram)[0xFFFE] = JSR_ABSOLUTE; 
    (*ram)[0xFFFF] = 0x00;
    (*ram)[0x0000] = 0x06;


    (*ram)[0x0600] = LDA_ZERO_PAGE;
    (*ram)[0x0601] = 0x10;  


    (*ram)[0x0010] = 0x84;  
}

int main(int argc, char* argv[]) {
    std::shared_ptr<RAM> ram = std::make_shared<RAM>();
    CPU cpu;

    cpu.ConnectRAM(ram);

    LoadTestProgram(ram);

    cpu.ResetCPU();

    std::cout << "Initial CPU State:" << std::endl;
    std::cout << "A: " << static_cast<int>(cpu.A) << std::endl;
    std::cout << "X: " << static_cast<int>(cpu.X) << std::endl;
    std::cout << "Y: " << static_cast<int>(cpu.Y) << std::endl;
    std::cout << "PC: " << cpu.PC << std::endl;
    std::cout << "SP: " << cpu.SP << std::endl;

    try {
        uint8_t cycles = 8;
        cpu.StepByInstruction(cycles);

        std::cout << "\nCPU State after LDA and JSR:" << std::endl;
        std::cout << "A: " << static_cast<int>(cpu.A) << std::endl;
        std::cout << "X: " << static_cast<int>(cpu.X) << std::endl;
        std::cout << "Y: " << static_cast<int>(cpu.Y) << std::endl;
        std::cout << "PC: " << cpu.PC << std::endl;
        std::cout << "SP: " << cpu.SP << std::endl;
        std::cout << "Flags (C,Z,I,D,B,V,N): "
            << cpu.flags.C << cpu.flags.Z << cpu.flags.I
            << cpu.flags.D << cpu.flags.B << cpu.flags.V
            << cpu.flags.N << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "CPU Error: " << e.what() << std::endl;
    }

    return 0;
}