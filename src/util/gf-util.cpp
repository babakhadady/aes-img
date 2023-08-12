#include "gf-util.hpp"
#include <cmath>

uint8_t GFMul(uint8_t a, uint8_t b)
{
  uint8_t p = 0;
  uint8_t c;

  for (int i = 0; i < 8; i++) {
    c = a & 0x80;
    if (b & 1) {
      p ^= a;
    }
    a = a << 1;
    if (c) {
      a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
    }
    b = b >> 1;
  }
  return p;
}

uint8_t LeftRotate(uint8_t val, uint8_t shift)
{
  return (val << shift) | (val >> (8 - shift));
}

uint8_t RightRotate(uint8_t val, uint8_t shift)
{
  return (val >> shift) | (val << (8 - shift));
}
