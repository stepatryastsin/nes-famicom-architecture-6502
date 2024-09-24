#include "Bus.hpp"

Bus::Bus()
{
	for (auto& a : RAM) {
		a = 0x0000;
    }
	cpu.conn(std::make_unique<Bus>(this));
}

void Bus::writed(uint16_t adr, uint8_t data)
{
	if (adr >= 0x0000 && adr <= 0xFFFF) {
		RAM[adr] = data;
	}
}

uint16_t Bus::readd(uint16_t adr, bool readOrWrite)
{
	if (adr >= 0x00 && adr <= 0xFFFF) {
		return RAM[adr];
	}
	return 0x0000;
}
