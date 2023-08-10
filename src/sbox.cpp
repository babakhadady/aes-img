#include "sbox.hpp"
#include "util/gf-util.hpp"
#include <cstdio>

SBox::SBox() { GenerateLogTables(); }

void SBox::ForwardSBox(uint8_t *pval)
{
  uint8_t val =
      *pval != 0 ? *pval != 1 ? antilog_arr[255 - log_arr[*pval]] : 1 : 0;
  *pval = val ^ LeftRotate(val, 1) ^ LeftRotate(val, 2) ^ LeftRotate(val, 3) ^
          LeftRotate(val, 4) ^ (uint8_t)99;
}

void SBox::GenerateLogTables()
{
  log_arr[0] = 0;
  antilog_arr[0] = 1;

  for (int i = 1; i <= 255; i++) {
    uint8_t x = GFMul(antilog_arr[i - 1], 3);
    antilog_arr[i] = x;
    log_arr[x] = i;
  }
}

void SBox::VisualizeSBox()
{

  printf("\n\n\n======================== VISUALIZING SBOX "
         "========================\n\n");
  printf("    ");

  for (int i = 0; i < 16; i++) {
    printf("%01x   ", i);
  }

  printf("\n");

  for (int i = 0; i < 16; i++) {
    printf("%01x  ", i);
    for (int j = 0, curr = 0; j < 16; j++) {
      curr = (i << 4) + j;
      ForwardSBox((uint8_t *)&curr);
      printf("%02x  ", curr);
    }
    printf("\n");
  }
}

uint8_t SBox::LeftRotate(uint8_t val, uint8_t shift)
{
  return (val << shift) | (val >> (8 - shift));
}

uint8_t SBox::RightRotate(uint8_t val, uint8_t shift)
{
  return (val >> shift) | (val << (8 - shift));
}
