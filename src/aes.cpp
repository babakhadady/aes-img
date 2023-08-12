#include "aes.hpp"
#include "./util/gf-util.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <vector>

uint8_t log_arr[255];
uint8_t antilog_arr[255];

AES::AES() { sbox = new SBox(); }

const uint8_t AES::mix_columns_matrix[4][4]{
    {2, 3, 1, 1}, {1, 2, 3, 1}, {1, 1, 2, 3}, {3, 1, 1, 2}};

vector<vector<uint8_t>> AES::AesEncrypt(vector<vector<uint8_t>> data,
                                        vector<uint8_t> key)
{
  /* InitialRoundKey(key); */

  /* InitialRound(data, key); */

  /* MainRound(data, key); */

  /* FinalRound(data, key); */
  return vector<vector<uint8_t>>{}; // STUB
}

vector<vector<uint8_t>> AES::AesDecrypt(vector<vector<uint8_t>> data,
                                        vector<vector<uint8_t>> key)
{
  return vector<vector<uint8_t>>{}; // STUB
}

void AES::AddRoundKey(vector<vector<uint8_t>> &data,
                      vector<vector<uint8_t>> key)
{
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      data[i][j] = data[i][j] ^ key[i][j];
    }
  }
}

void AES::MixColumns(vector<vector<uint8_t>> &data)
{

  for (int i = 0; i < data[0].size(); i++) {
    vector<uint8_t> curr(0);

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

/* Generates initial 16 byte key
 * TODO: Support for 192 and 256 bit keys
 * */
vector<vector<uint8_t>> AES::InitialRoundKey(vector<uint8_t> key)
{

  vector<vector<uint8_t>> initial_key;

  for (int i = 0; i < key.size(); i += 4) {
    initial_key.push_back({key[i], key[i + 1], key[i + 2], key[i + 3]});
  }

  return initial_key;
}

int AES::RoundConstant(int i)
{
  if (i < 1) {
    throw std::invalid_argument("RoundConstant: i must be >= 1");
  }

  if (i == 1) {
    return 1;
  }

  return GFMul(RoundConstant(i - 1), 2);
}

void AES::NextRoundKey(vector<vector<uint8_t>> key)
{
  // STUB
}

void AES::Test()
{
  /* vector<uint8_t> key{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
   */

  /* for (auto i : InitialRoundKey(key)) { */
  /*   for (auto j : i) */
  /*     printf("%d", j); */
  /*   printf("\n"); */
  /* } */

  for (int i = 1; i <= 10; i++) {
    printf("%d: ", i);
    printf("%x\n", RoundConstant(i));
  }
}
