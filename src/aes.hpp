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

  vector<vector<uint8_t>> InitialRoundKey(vector<uint8_t> key);
  vector<vector<uint8_t>> NextRoundKey(vector<vector<uint8_t>> key, int round);
  vector<uint8_t> GenerateFirstWord(vector<uint8_t> w1, vector<uint8_t> w2,
                                    int round);
  vector<uint8_t> GenerateNextWord(vector<uint8_t> w1, vector<uint8_t> w2);
  uint8_t RoundConstant(int i);

  void ShiftRow(vector<uint8_t> &data, int shift);
  vector<uint8_t> MixColumn(vector<uint8_t> column);

  void InitialRound(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key);
  void CoreRound(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key);
  void FinalRound(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key);
  void PrintData(vector<vector<uint8_t>> data, std::string title);

public:
  AES();
  vector<vector<uint8_t>> AesEncrypt(vector<vector<uint8_t>> data,
                                     vector<uint8_t> key);
  vector<vector<uint8_t>> AesDecrypt(vector<vector<uint8_t>> data,
                                     vector<vector<uint8_t>> key);

  void SubBytes(vector<vector<uint8_t>> &data);
  void ShiftRows(vector<vector<uint8_t>> &data);
  void MixColumns(vector<vector<uint8_t>> &data);
  void AddRoundKey(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key);

  void Test();
};

#endif
