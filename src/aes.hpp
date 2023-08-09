#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include <cstdint>
#include <vector>

using std::vector;

class AES {

private:
  SBox *sbox;
  void SubBytes(vector<vector<uint8_t>> &data);

public:
  AES();
  vector<vector<uint8_t>> AesEncrypt(vector<vector<uint8_t>> data,
                                     vector<vector<uint8_t>> key);
  vector<vector<uint8_t>> AesDecrypt(vector<vector<uint8_t>> data,
                                     vector<vector<uint8_t>> key);

  void Test();
};

#endif
