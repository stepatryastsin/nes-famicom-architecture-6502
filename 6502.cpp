#include "6502.hpp"

void A6502::writed(uint16_t adr, uint8_t data)
{
	bus->writed(adr, data);
}

uint16_t A6502::readd(uint16_t adr)
{
	bus->readd(adr, false);
}
