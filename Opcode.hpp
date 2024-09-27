#include<iostream>

/// LDA
static constexpr uint8_t LDA_IMIDEATE           = 0xA9;
static constexpr uint8_t LDA_ZERO_PAGE          = 0xA5;
static constexpr uint8_t LDA_ZERO_PAGE_OFFSET_X = 0xB5;
static constexpr uint8_t LDA_ABSOLUTE           = 0xAD;
static constexpr uint8_t LDA_ABSOLUTE_OFFSET_X  = 0xBD;
static constexpr uint8_t LDA_ABSOLUTE_OFFSET_Y  = 0xB9;
static constexpr uint8_t LDA_INDIRECT_OFFSET_X  = 0xA1;
static constexpr uint8_t LDA_INDIRECT_OFFSET_Y  = 0xB1;

/// /////////////////////////////////////////


static constexpr uint8_t JSR_ABSOLUTE   = 0x20;
