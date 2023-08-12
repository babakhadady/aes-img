#ifndef gf_util
#define gf_util

#include <cmath>
#include <cstdint>

uint8_t GFMul(uint8_t a, uint8_t b);
uint8_t LeftRotate(uint8_t val, uint8_t shift);
uint8_t RightRotate(uint8_t val, uint8_t shift);
uint32_t RightRotate(uint32_t val, uint8_t shift);
uint32_t LeftRotate(uint32_t val, uint8_t shift);

#endif
