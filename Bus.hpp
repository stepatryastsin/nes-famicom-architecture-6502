#ifndef BUS_H
#define BUS_H
#include<array>
#include<inttypes.h>
#include "6502.hpp"
class Bus {
public:
	 Bus();
	~Bus();
	void writed(uint16_t adr, uint8_t data);
	uint16_t readd(uint16_t adr,bool readOrWrite = false);
public:
	A6502 cpu;
	std::array<uint16_t, 64 * 1024> RAM;
};
#endif // !BUS_H
