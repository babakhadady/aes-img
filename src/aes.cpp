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

/* TODO: Support for 192 and 256 bit keys */
vector<vector<uint8_t>> AES::InitialRoundKey(vector<uint8_t> key)
{

  vector<vector<uint8_t>> initial_key;

  for (int i = 0; i < key.size(); i += 4) {
    initial_key.push_back({key[i], key[i + 1], key[i + 2], key[i + 3]});
  }

  return initial_key;
}

vector<vector<uint8_t>> AES::NextRoundKey(vector<vector<uint8_t>> key,
                                          int round)
{

  vector<vector<uint8_t>> next_key{GenerateFirstWord(key[0], round)};

  for (int i = 1; i < 2; i++) {
    next_key.push_back(GenerateNextWord(key[i], next_key[i - 1]));
  }

  return next_key;
}

vector<uint8_t> AES::GenerateNextWord(vector<uint8_t> w1, vector<uint8_t> w2)
{
  vector<uint8_t> next_word;
  for (int i = 0; i < w1.size(); i++) {
    next_word.push_back(w1[i] ^ w2[i]);
  }
  return next_word;
}

vector<uint8_t> AES::GenerateFirstWord(vector<uint8_t> word, int round)
{

  vector<uint8_t> rc = {RoundConstant(round), 0x00, 0x00, 0x00};

  uint32_t shift =
      LeftRotate((uint32_t)((uint32_t)word[0] << 24 | (uint32_t)word[1] << 16 |
                            (uint32_t)word[2] << 8 | (uint32_t)word[3]),
                 1);

  vector<uint8_t> next_word = {
      (uint8_t)(shift >> 24),
      (uint8_t)(shift >> 16),
      (uint8_t)(shift >> 8),
      (uint8_t)(shift & 0xFF),
  };

  vector<vector<uint8_t>> temp = {next_word};
  SubBytes(temp);

  next_word = temp[0];

  for (int i = 0; i < 4; i++) {
    next_word[i] = next_word[i] ^ rc[i];
  }

  return next_word;
}

uint8_t AES::RoundConstant(int i)
{
  if (i < 1) {
    throw std::invalid_argument("RoundConstant: i must be >= 1");
  }

  if (i == 1) {
    return 1;
  }

  return GFMul(RoundConstant(i - 1), 2);
}

void AES::Test()
{
  /* vector<vector<uint8_t>> key{ */
  /*     {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}; */

  /* vector<vector<uint8_t>> data = { */
  /*     {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}; */
  /* AddRoundKey(data, key); */

  /* for (auto i : data) { */
  /*   for (auto j : i) */
  /*     printf("%d ", j); */
  /*   printf("\n"); */
  /* } */

  for (auto i : GenerateFirstWord({0xF0, 0x88, 0x80, 0x00}, 1)) {

    printf("%x ", i);
  }
}
