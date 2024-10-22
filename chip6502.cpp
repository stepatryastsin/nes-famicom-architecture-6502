#include "chip6502.h"

CHIP6502::CHIP6502()
{
	std::fill(ram.begin(), ram.end(), 0x00);
	instruction = {
		{  [this]() {BRK(); },[this]() {IMM(); }, 7 },
		{  [this]() {ORA(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 3 },
		{  [this]() {ORA(); },[this]() {ZP0(); }, 3 },
		{  [this]() {ASL(); },[this]() {ZP0(); }, 5 },
		{  [this]() {PHP(); },[this]() {IMP(); }, 3 },
		{  [this]() {ORA(); },[this]() {IMM(); }, 2 },
		{  [this]() {ASL(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {ORA(); },[this]() {ABS(); }, 4 },
		{  [this]() {ASL(); },[this]() {ABS(); }, 6 },
		{  [this]() {BPL(); },[this]() {REL(); }, 2 },
		{  [this]() {ORA(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {ORA(); },[this]() {ZPX(); }, 4 },
		{  [this]() {ASL(); },[this]() {ZPX(); }, 6 },
		{  [this]() {CLC(); },[this]() {IMP(); }, 2 },
		{  [this]() {ORA(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {ORA(); },[this]() {ABX(); }, 4 },
		{  [this]() {ASL(); },[this]() {ABX(); }, 7 },
		{  [this]() {JSR(); },[this]() {ABS(); }, 6 },
		{  [this]() {AND(); },[this]() {IZX(); }, 6 },
		{  [this]() {BIT(); },[this]() {ZP0(); }, 3 },
		{  [this]() {AND(); },[this]() {ZP0(); }, 3 },
		{  [this]() {ROL(); },[this]() {ZP0(); }, 5 },
		{  [this]() {PLP(); },[this]() {IMP(); }, 4 },
		{  [this]() {AND(); },[this]() {IMM(); }, 2 },
		{  [this]() {ROL(); },[this]() {IMP(); }, 2 },
		{  [this]() {BIT(); },[this]() {ABS(); }, 4 },
		{  [this]() {AND(); },[this]() {ABS(); }, 4 },
		{  [this]() {ROL(); },[this]() {ABS(); }, 6 },
		{  [this]() {BMI(); },[this]() {REL(); }, 2 },
		{  [this]() {AND(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {AND(); },[this]() {ZPX(); }, 4 },
		{  [this]() {ROL(); },[this]() {ZPX(); }, 6 },
		{  [this]() {SEC(); },[this]() {IMP(); }, 2 },
		{  [this]() {AND(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {AND(); },[this]() {ABX(); }, 4 },
		{  [this]() {ROL(); },[this]() {ABX(); }, 7 },
		{  [this]() {RTI(); },[this]() {IMP(); }, 6 },
		{  [this]() {EOR(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 3 },
		{  [this]() {EOR(); },[this]() {ZP0(); }, 3 },
		{  [this]() {LSR(); },[this]() {ZP0(); }, 5 },
		{  [this]() {PHA(); },[this]() {IMP(); }, 3 },
		{  [this]() {EOR(); },[this]() {IMM(); }, 2 },
		{  [this]() {LSR(); },[this]() {IMP(); }, 2 },
		{  [this]() {JMP(); },[this]() {ABS(); }, 3 },
		{  [this]() {EOR(); },[this]() {ABS(); }, 4 },
		{  [this]() {LSR(); },[this]() {ABS(); }, 6 },
		{  [this]() {BVC(); },[this]() {REL(); }, 2 },
		{  [this]() {EOR(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {EOR(); },[this]() {ZPX(); }, 4 },
		{  [this]() {LSR(); },[this]() {ZPX(); }, 6 },
		{  [this]() {CLI(); },[this]() {IMP(); }, 2 },
		{  [this]() {EOR(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {EOR(); },[this]() {ABX(); }, 4 },
		{  [this]() {LSR(); },[this]() {ABX(); }, 7 },
		{  [this]() {RTS(); },[this]() {IMP(); }, 6 },
		{  [this]() {ADC(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 3 },
		{  [this]() {ADC(); },[this]() {ZP0(); }, 3 },
		{  [this]() {ROR(); },[this]() {ZP0(); }, 5 },
		{  [this]() {PLA(); },[this]() {IMP(); }, 4 },
		{  [this]() {ADC(); },[this]() {IMM(); }, 2 },
		{  [this]() {ROR(); },[this]() {IMP(); }, 2 },
		{  [this]() {JMP(); },[this]() {IND(); }, 5 },
		{  [this]() {ADC(); },[this]() {ABS(); }, 4 },
		{  [this]() {ROR(); },[this]() {ABS(); }, 6 },
		{  [this]() {BVS(); },[this]() {REL(); }, 2 },
		{  [this]() {ADC(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {ADC(); },[this]() {ZPX(); }, 4 },
		{  [this]() {ROR(); },[this]() {ZPX(); }, 6 },
		{  [this]() {SEI(); },[this]() {IMP(); }, 2 },
		{  [this]() {ADC(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {ADC(); },[this]() {ABX(); }, 4 },
		{  [this]() {ROR(); },[this]() {ABX(); }, 7 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {STA(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {STY(); },[this]() {ZP0(); }, 3 },
		{  [this]() {STA(); },[this]() {ZP0(); }, 3 },
		{  [this]() {STX(); },[this]() {ZP0(); }, 3 },
		{  [this]() {DEY(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {TXA(); },[this]() {IMP(); }, 2 },
		{  [this]() {STY(); },[this]() {ABS(); }, 4 },
		{  [this]() {STA(); },[this]() {ABS(); }, 4 },
		{  [this]() {STX(); },[this]() {ABS(); }, 4 },
		{  [this]() {BCC(); },[this]() {REL(); }, 2 },
		{  [this]() {STA(); },[this]() {IZY(); }, 6 },
		{  [this]() {STY(); },[this]() {ZPX(); }, 4 },
		{  [this]() {STA(); },[this]() {ZPX(); }, 4 },
		{  [this]() {STX(); },[this]() {ZPY(); }, 4 },
		{  [this]() {TYA(); },[this]() {IMP(); }, 2 },
		{  [this]() {STA(); },[this]() {ABY(); }, 5 },
		{  [this]() {TXS(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 5 },
		{  [this]() {STA(); },[this]() {ABX(); }, 5 },
		{  [this]() {LDY(); },[this]() {IMM(); }, 2 },
		{  [this]() {LDA(); },[this]() {IZX(); }, 6 },
		{  [this]() {LDX(); },[this]() {IMM(); }, 2 },
		{  [this]() {LDY(); },[this]() {ZP0(); }, 3 },
		{  [this]() {LDA(); },[this]() {ZP0(); }, 3 },
		{  [this]() {LDX(); },[this]() {ZP0(); }, 3 },
		{  [this]() {TAY(); },[this]() {IMP(); }, 2 },
		{  [this]() {LDA(); },[this]() {IMM(); }, 2 },
		{  [this]() {TAX(); },[this]() {IMP(); }, 2 },
		{  [this]() {LDY(); },[this]() {ABS(); }, 4 },
		{  [this]() {LDA(); },[this]() {ABS(); }, 4 },
		{  [this]() {LDX(); },[this]() {ABS(); }, 4 },
		{  [this]() {BCS(); },[this]() {REL(); }, 2 },
		{  [this]() {LDA(); },[this]() {IZY(); }, 5 },
		{  [this]() {LDY(); },[this]() {ZPX(); }, 4 },
		{  [this]() {LDA(); },[this]() {ZPX(); }, 4 },
		{  [this]() {LDX(); },[this]() {ZPY(); }, 4 },
		{  [this]() {CLV(); },[this]() {IMP(); }, 2 },
		{  [this]() {LDA(); },[this]() {ABY(); }, 4 },
		{  [this]() {TSX(); },[this]() {IMP(); }, 2 },
		{  [this]() {LDY(); },[this]() {ABX(); }, 4 },
		{  [this]() {LDA(); },[this]() {ABX(); }, 4 },
		{  [this]() {LDX(); },[this]() {ABY(); }, 4 },
		{  [this]() {CPY(); },[this]() {IMM(); }, 2 },
		{  [this]() {CMP(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {CPY(); },[this]() {ZP0(); }, 3 },
		{  [this]() {CMP(); },[this]() {ZP0(); }, 3 },
		{  [this]() {DEC(); },[this]() {ZP0(); }, 5 },
		{  [this]() {INY(); },[this]() {IMP(); }, 2 },
		{  [this]() {CMP(); },[this]() {IMM(); }, 2 },
		{  [this]() {DEX(); },[this]() {IMP(); }, 2 },
		{  [this]() {CPY(); },[this]() {ABS(); }, 4 },
		{  [this]() {CMP(); },[this]() {ABS(); }, 4 },
		{  [this]() {DEC(); },[this]() {ABS(); }, 6 },
		{  [this]() {BNE(); },[this]() {REL(); }, 2 },
		{  [this]() {CMP(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {CMP(); },[this]() {ZPX(); }, 4 },
		{  [this]() {DEC(); },[this]() {ZPX(); }, 6 },
		{  [this]() {CLD(); },[this]() {IMP(); }, 2 },
		{  [this]() {CMP(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {CMP(); },[this]() {ABX(); }, 4 },
		{  [this]() {DEC(); },[this]() {ABX(); }, 7 },
		{  [this]() {CPX(); },[this]() {IMM(); }, 2 },
		{  [this]() {SBC(); },[this]() {IZX(); }, 6 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {CPX(); },[this]() {ZP0(); }, 3 },
		{  [this]() {SBC(); },[this]() {ZP0(); }, 3 },
		{  [this]() {INC(); },[this]() {ZP0(); }, 5 },
		{  [this]() {INX(); },[this]() {IMP(); }, 2 },
		{  [this]() {SBC(); },[this]() {IMM(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {SBC(); },[this]() {IMP(); }, 2 },
		{  [this]() {CPX(); },[this]() {ABS(); }, 4 },
		{  [this]() {SBC(); },[this]() {ABS(); }, 4 },
		{  [this]() {INC(); },[this]() {ABS(); }, 6 },
		{  [this]() {BEQ(); },[this]() {REL(); }, 2 },
		{  [this]() {SBC(); },[this]() {IZY(); }, 5 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {SBC(); },[this]() {ZPX(); }, 4 },
		{  [this]() {INC(); },[this]() {ZPX(); }, 6 },
		{  [this]() {SED(); },[this]() {IMP(); }, 2 },
		{  [this]() {SBC(); },[this]() {ABY(); }, 4 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 2 },
		{  [this]() {NOP(); },[this]() {IMP(); }, 4 },
		{  [this]() {SBC(); },[this]() {ABX(); }, 4 },
		{  [this]() {INC(); },[this]() {ABX(); }, 7 },
	};
}

uint8_t CHIP6502::read(uint16_t address) const
{
	return ram[address];
}

void CHIP6502::write(uint16_t address, uint8_t data)
{
	ram[address] = data;
}

uint16_t CHIP6502::readWord(uint16_t address)
{
	uint8_t f = read(address);
	uint8_t s = read(address+1);
	return (s << 8) | f;
}

void CHIP6502::incrementPC(uint8_t amount)
{
	pc += amount;
}

uint16_t CHIP6502::fetchWordFromPC()
{
	uint16_t word = readWord(pc);
	incrementPC(2);
	return word;
}

uint8_t CHIP6502::IMP()
{
	fetched = a;
	return 0;
}

uint8_t CHIP6502::IMM()
{
	addr_abs = pc++;
	return 0;
}

uint8_t CHIP6502::ZP0()
{
	addr_abs = read(pc);
	incrementPC();
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CHIP6502::ZPX()
{
	addr_abs = read(pc) + x;
	incrementPC();
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CHIP6502::ZPY()
{
	addr_abs = read(pc) + y;
	incrementPC();
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CHIP6502::REL()
{
	addr_rel = read(pc);
	incrementPC();
	if (addr_rel & 0x80) {
		addr_rel |= 0xFF00;
	}
	return 0;
}

uint8_t CHIP6502::ABS()
{
	addr_rel = fetchWordFromPC();
	return 0;
}

uint8_t CHIP6502::ABX()
{
	addr_rel = fetchWordFromPC()+x;
	return 0;
}

uint8_t CHIP6502::ABY()
{
	addr_rel = fetchWordFromPC() + y;
	return 0;
}

uint8_t CHIP6502::IND()
{
	uint16_t ptr = fetchWordFromPC();
	addr_abs = readWord(ptr);
	return 0;
}

uint8_t CHIP6502::IZX()
{
	uint16_t t = (read(pc) + x) & 0x00FF;
	incrementPC();
	addr_abs = readWord(t);
	return 0;
}

uint8_t CHIP6502::IZY()
{
	uint16_t t = read(pc) & 0x00FF;
	incrementPC();
	addr_abs = readWord(t) + y;
	return ((addr_abs & 0xFF00) != (readWord(t) & 0xFF00)) ? 1 : 0;
}
