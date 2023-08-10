#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include <cstdint>
#include <vector>

using std::vector;

class AES {

private:
  /* const uint8_t mix_columns_matrix[] = */
  /* [ [ 2, 3, 1, 1 ], [ 1, 2, 3, 1 ], [ 1, 1, 2, 3 ], [ 3, 1, 1, 2 ] ]; */
  SBox *sbox;
  void AddRoundKey(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> &key);
  void ShiftRow(vector<uint8_t> &data, int shift);

public:
  AES();
  vector<vector<uint8_t>> AesEncrypt(vector<vector<uint8_t>> data,
                                     vector<vector<uint8_t>> key);
  vector<vector<uint8_t>> AesDecrypt(vector<vector<uint8_t>> data,
                                     vector<vector<uint8_t>> key);

  void SubBytes(vector<vector<uint8_t>> &data);
  void ShiftRows(vector<vector<uint8_t>> &data);
  void MixColumns(vector<vector<uint8_t>> &data);

  void Test();
};

#endif
