#include "aes.hpp"
#include "./util/gf-util.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <vector>

#define VERBOSE 0

uint8_t log_arr[255];
uint8_t antilog_arr[255];

AES::AES() { sbox = new SBox(); }

const uint8_t AES::mix_columns_matrix[4][4]{
    {2, 3, 1, 1}, {1, 2, 3, 1}, {1, 1, 2, 3}, {3, 1, 1, 2}};

vector<vector<uint8_t>> AES::AesEncrypt(vector<vector<uint8_t>> &data,
                                        vector<uint8_t> key)
{
  vector<vector<uint8_t>> curr_key = InitialRoundKey(key);

  if (VERBOSE) {
    PrintData(data, "=== INITIAL DATA ===");
  }

  InitialRound(data, curr_key);
  int i;
  for (i = 1; i < 10; i++) {

    if (VERBOSE) {
      PrintData(data, "\n\n\n=== ROUND " + std::to_string(i) + " ===");
    }

    curr_key = NextRoundKey(curr_key, i);
    CoreRound(data, curr_key);
  }

  if (VERBOSE) {
    PrintData(data, "\n\n\n=== ROUND " + std::to_string(i) + " ===");
  }

  curr_key = NextRoundKey(curr_key, 10);
  FinalRound(data, curr_key);
  return data;
}

vector<vector<uint8_t>> AES::AesDecrypt(vector<vector<uint8_t>> &data,
                                        vector<vector<uint8_t>> key)
{
  return vector<vector<uint8_t>>{}; // STUB
}

void AES::InitialRound(vector<vector<uint8_t>> &data,
                       vector<vector<uint8_t>> key)
{
  AddRoundKey(data, key);
}

void AES::CoreRound(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key)
{

  SubBytes(data);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER SUBBYTES -");
  }

  ShiftRows(data);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER SHIFTROWS -");
  }

  MixColumns(data);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER MIXCOLUMNS -");
  }

  AddRoundKey(data, key);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER ADDROUNDKEY -");
  }
}

void AES::FinalRound(vector<vector<uint8_t>> &data, vector<vector<uint8_t>> key)
{
  SubBytes(data);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER SUBBYTES -");
  }

  ShiftRows(data);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER SHIFTROWS -");
  }

  AddRoundKey(data, key);
  if (VERBOSE) {
    PrintData(data, "\n- AFTER ADDROUNDKEY -");
  }
}

void AES::AddRoundKey(vector<vector<uint8_t>> &data,
                      vector<vector<uint8_t>> key)
{
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      data[i][j] ^= key[i][j];
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

  vector<vector<uint8_t>> next_key{
      GenerateFirstWord({key[0][3], key[1][3], key[2][3], key[3][3]},
                        {key[0][0], key[1][0], key[2][0], key[3][0]}, round)};

  for (int i = 1; i < 4; i++) {
    next_key.push_back(GenerateNextWord(
        {key[0][i], key[1][i], key[2][i], key[3][i]}, next_key[i - 1]));
  }

  /* PrintData(next_key, "key\n"); */

  vector<vector<uint8_t>> next_key_rotated;

  for (int i = 0; i < next_key.size(); i++) {
    next_key_rotated.push_back(
        {next_key[0][i], next_key[1][i], next_key[2][i], next_key[3][i]});
  }

  if (VERBOSE) {
    PrintData(next_key_rotated, "\n~ KEY ~ ");
  }

  return next_key_rotated;
}

vector<uint8_t> AES::GenerateNextWord(vector<uint8_t> w1, vector<uint8_t> w2)
{
  vector<uint8_t> next_word;
  for (int i = 0; i < w1.size(); i++) {
    next_word.push_back(w1[i] ^ w2[i]);
  }
  return next_word;
}

vector<uint8_t> AES::GenerateFirstWord(vector<uint8_t> w1, vector<uint8_t> w2,
                                       int round)
{

  vector<uint8_t> rc = {RoundConstant(round), 0x00, 0x00, 0x00};

  uint32_t shift =
      LeftRotate((uint32_t)((uint32_t)w1[0] << 24 | (uint32_t)w1[1] << 16 |
                            (uint32_t)w1[2] << 8 | (uint32_t)w1[3]),
                 8);

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

  for (int i = 0; i < 4; i++) {
    next_word[i] = next_word[i] ^ w2[i];
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

void AES::PrintData(vector<vector<uint8_t>> data, std::string title)
{
  std::cout << title << std::endl;

  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data.size(); j++) {
      printf("%x", data[i][j]);
    }
    printf(" ");
  }
  printf("\n");
}

void AES::Test()
{
  vector<uint8_t> prevKey = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x31};

  /* vector<uint8_t> prevKey = {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6d, 0x79,
   */

  /*                            0x20, 0x4b, 0x75, 0x6e, 0x67, 0x20, 0x46, 0x75};
   */

  /* vector<vector<uint8_t>> data = {{0x01, 0x4B, 0xAF, 0x22}, */
  /*                                 {0x78, 0xA6, 0x9D, 0x33}, */
  /*                                 {0x1D, 0x51, 0x80, 0x10}, */
  /*                                 {0x36, 0x43, 0xE9, 0x9A}}; */

  vector<vector<uint8_t>> data = {{0xaa, 0xbb, 0xcc, 0xdd},
                                  {0xff, 0xff, 0xff, 0xff},
                                  {0xff, 0xff, 0xff, 0xff},
                                  {0xff, 0xff, 0xff, 0xff}};

  /* vector<vector<uint8_t>> data = {{0x54, 0x77, 0x6f, 0x20}, */
  /*                                 {0x4f, 0x6e, 0x65, 0x20}, */
  /*                                 {0x43, 0x69, 0x6e, 0x25}, */
  /*                                 {0x20, 0x54, 0x77, 0x6f}}; */

  data = AesEncrypt(data, prevKey);

  PrintData(data, "\n\nFINAL DATA");
}
