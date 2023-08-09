#ifndef SBOX_H
#define SBOX_H

#include <cstdint>

class SBox {
private:
  uint8_t log_arr[255];
  uint8_t antilog_arr[255];

  uint8_t LeftRotate(uint8_t val, uint8_t shift);
  uint8_t RightRotate(uint8_t val, uint8_t shift);
  uint8_t GFMul(uint8_t a, uint8_t b);
  void GenerateLogTables();

public:
  void ForwardSBox(uint8_t *pval);
  void VisualizeSBox();
  SBox();
};

#endif
