#include "aes.hpp"
#include "./util/gf-util.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <vector>

uint8_t log_arr[255];
uint8_t antilog_arr[255];

AES::AES() { sbox = new SBox(); }

const uint8_t AES::mix_columns_matrix[4][4]{
    {2, 3, 1, 1}, {1, 2, 3, 1}, {1, 1, 2, 3}, {3, 1, 1, 2}};

vector<vector<uint8_t>> AES::AesDecrypt(vector<vector<uint8_t>> data,
                                        vector<vector<uint8_t>> key)
{
}

vector<vector<uint8_t>> AES::AesEncrypt(vector<vector<uint8_t>> data,
                                        vector<vector<uint8_t>> key)
{
}

void AES::MixColumns(vector<vector<uint8_t>> &data)
{

  for (int i = 0; i < data[0].size(); i++) {
    vector<uint8_t> curr;
    for (int j = 0; j < data.size(); j++) {
      curr.push_back(data[j][i]);
    }

    vector<uint8_t> mixed_col = MixColumn(curr);
    for (int j = 0; j < data.size(); j++) {
      data[j][i] = mixed_col[j];
    }
  }
}

void AES::SubBytes(vector<vector<uint8_t>> &data)
{
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      sbox->ForwardSBox(&data[i][j]);
    }
  }
}

void AES::ShiftRows(vector<vector<uint8_t>> &data)
{
  for (int i = 0; i < data.size(); i++) {
    ShiftRow(data[i], i);
  }
}

/** TODO: OPTIMIZE IMPLEMENTATION**/
void AES::ShiftRow(vector<uint8_t> &data, int shift)
{
  while (shift > 0) {
    uint8_t prev = data[0];
    for (int i = data.size() - 1; i >= 0; i--) {
      uint8_t temp = data[i];
      data[i] = prev;
      prev = temp;
    }
    shift--;
  }
}

vector<uint8_t> AES::MixColumn(vector<uint8_t> column)
{
  vector<uint8_t> mixed_columns;

  for (int i = 0; i < 4; i++) {
    uint8_t val = 0;
    for (int j = 0; j < 4; j++) {
      val ^= GFMul(column[j], mix_columns_matrix[i][j]);
    }
    mixed_columns.push_back(val);
  }

  return mixed_columns;
}

void AES::Test()
{
  vector<vector<uint8_t>> test{{{1, 219}, {1, 19}, {1, 83}, {1, 69}}};
  MixColumns(test);

  for (auto i : test) {
    for (auto j : i) {
      printf("%d ", j);
    }
    printf("\n");
  }
}
