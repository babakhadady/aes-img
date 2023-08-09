#include "aes.hpp"
#include <cmath>
#include <sys/types.h>
#include <vector>

#include <cstdio>
#include <iostream>

uint8_t log_arr[255];
uint8_t antilog_arr[255];

AES::AES() { sbox = new SBox(); }

vector<vector<uint8_t>> AES::AesDecrypt(vector<vector<uint8_t>> data,
                                        vector<vector<uint8_t>> key)
{
}

vector<vector<uint8_t>> AES::AesEncrypt(vector<vector<uint8_t>> data,
                                        vector<vector<uint8_t>> key)
{
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
    for (int i =  data.size() - 1; i >= 0; i--) {
      uint8_t temp = data[i];
      data[i] = prev;
      prev = temp;
    }
	shift--;
  }
}

void AES::Test()
{
  vector<vector<uint8_t>> test{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13,14,15,16}, {17,18,19,20}};
  ShiftRows(test);

  for (int i = 0; i < test.size(); i++) {
    for (int j = 0; j < test[i].size(); j++) {
      printf("%d ", test[i][j]);
    }
    printf("\n");
  }
}
