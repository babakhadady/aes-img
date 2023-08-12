#ifndef SBOX_H
#define SBOX_H

#include <cstdint>

class SBox {
private:
  uint8_t log_arr[255];
  uint8_t antilog_arr[255];

  void GenerateLogTables();

public:
  void ForwardSBox(uint8_t *pval);
  void VisualizeSBox();
  SBox();
};

#endif
