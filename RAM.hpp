#ifndef RAM_H
#define RAM_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#define MEM_SIZE 1024*64
class CPU;  // Forward declaration
class RAM {
public:
    std::vector<uint16_t> memory;
    RAM();
    void Init();


    uint16_t operator[](uint16_t address) const;
    uint16_t& operator[](uint16_t address);


private:
    std::shared_ptr<CPU> cpu; 
    void ConnectCPU(std::shared_ptr<CPU> cpuPtr); 
    friend class CPU;  
};

#endif // RAM_H
