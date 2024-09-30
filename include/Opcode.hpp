#include<iostream>

//////////////////////// LDA //////////////////////////
static constexpr uint8_t LDA_IMIDEATE           = 0xA9;
static constexpr uint8_t LDA_ZERO_PAGE          = 0xA5;
static constexpr uint8_t LDA_ABSOLUTE           = 0xAD;
static constexpr uint8_t LDA_ZERO_PAGE_OFFSET_X = 0xB5;
static constexpr uint8_t LDA_ABSOLUTE_OFFSET_X  = 0xBD;
static constexpr uint8_t LDA_ABSOLUTE_OFFSET_Y  = 0xB9;
static constexpr uint8_t LDA_INDIRECT_OFFSET_X  = 0xA1;
static constexpr uint8_t LDA_INDIRECT_OFFSET_Y  = 0xB1;
///////////////////////////////////////////////////////

//////////////////////// LDX //////////////////////////
static constexpr uint8_t LDX_IMIDEATE           = 0xA2;
static constexpr uint8_t LDX_ZERO_PAGE          = 0xA6;
static constexpr uint8_t LDX_ABSOLUTE           = 0xAE;
static constexpr uint8_t LDX_ZERO_PAGE_OFFSET_Y = 0xB6;
static constexpr uint8_t LDX_ABSOLUTE_OFFSET_Y  = 0xBE;
///////////////////////////////////////////////////////

//////////////////////// LDY //////////////////////////
static constexpr uint8_t LDY_IMIDEATE           = 0xA0;
static constexpr uint8_t LDY_ZERO_PAGE          = 0xA4;
static constexpr uint8_t LDY_ABSOLUTE           = 0xAC;
static constexpr uint8_t LDY_ZERO_PAGE_OFFSET_X = 0xB4;
static constexpr uint8_t LDY_ABSOLUTE_OFFSET_X  = 0xBC;
///////////////////////////////////////////////////////

//////////////////////// STA //////////////////////////
static constexpr uint8_t STA_ZERO_PAGE          = 0x85;
static constexpr uint8_t STA_ABSOLUTE           = 0x8D;
static constexpr uint8_t STA_ZERO_PAGE_OFFSET_X = 0x95;
static constexpr uint8_t STA_ABSOLUTE_OFFSET_X  = 0x9D;
static constexpr uint8_t STA_ABSOLUTE_OFFSET_Y  = 0x99;
static constexpr uint8_t STA_INDIRECT_OFFSET_X  = 0x81;
static constexpr uint8_t STA_INDIRECT_OFFSET_Y  = 0x91;
///////////////////////////////////////////////////////

//////////////////////// STX //////////////////////////
static constexpr uint8_t STX_ZERO_PAGE          = 0x86;
static constexpr uint8_t STX_ABSOLUTE           = 0x96;
static constexpr uint8_t STX_ZERO_PAGE_OFFSET_Y = 0x8E;
///////////////////////////////////////////////////////

//////////////////////// STY //////////////////////////
static constexpr uint8_t STY_ZERO_PAGE          = 0x84;
static constexpr uint8_t STY_ABSOLUTE           = 0x8C;
static constexpr uint8_t STY_ZERO_PAGE_OFFSET_X = 0x94;
///////////////////////////////////////////////////////


static constexpr uint8_t JSR_ABSOLUTE   = 0x20;
