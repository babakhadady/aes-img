#ifndef AES_H
#define AES_H

#include "sbox.hpp"
#include <cstdint>
#include <vector>

using std::vector;

class AES {

private:
  static const uint8_t mix_columns_matrix[4][4];
  SBox *sbox;
  void AddRoundKey(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> &key);
  void ShiftRow(vector<uint8_t> &data, int shift);
	vector<uint8_t> MixColumn(vector<uint8_t> column);

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
