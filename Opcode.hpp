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


static constexpr uint8_t JSR_ABSOLUTE   = 0x20;
