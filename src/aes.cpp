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

void AES::Test()
{
  vector<vector<uint8_t>> test{{0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9}};
  SubBytes(test);
  printf("\n");

  for (int i = 0; i < test[0].size(); i++) {
                printf("%x ", test[0][i]);
  }
  printf("\n");
	sbox->VisualizeSBox();
}
