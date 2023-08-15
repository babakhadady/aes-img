#include "../lib/cs221util/PNG.h"
#include "aes.hpp"

#include <iostream>
#include <string>

using namespace cs221util;

int main(int argc, char *argv[])
{

  if (argc == 1) {
    printf("Please Specify a File to Encrypt\n");
    return -1;
  }
  std::string file_name = argv[1];

  PNG *png = new PNG();

  if (png->readFromFile(file_name) == 0) {
    return -1;
  }

  cout << "File to Encrypt: " << file_name << endl;
  vector<vector<uint8_t>> data;

  for (int i = 0; i < png->width(); i++) {
    for (int j = 0; j < png->height(); j++) {
      RGBAPixel *pixel = png->getPixel(i, j);
      data.push_back(
          {pixel->r, pixel->g, pixel->b, (uint8_t)floor(pixel->a * 255)});
    }
  }

  for (int i = 0; i < (png->width() * png->height() % 128); i++) {
    i == 0 ? data.push_back({0x80, 0x00, 0x00, 0x00})
           : data.push_back({0x00, 0x00, 0x00, 0x00});
  }

  AES *aes = new AES();

  vector<vector<uint8_t>> data_enc;

  for (int i = 0; i < data.size(); i += 4) {
    vector<vector<uint8_t>> temp{data[i], data[i + 1], data[i + 2],
                                 data[i + 3]};

    if (i != 0) {
      /* aes->CipherBlockChain */
    }

    aes->AesEncrypt(temp, {0xff, 0xff, 0xff, 0xaf, 0xbf, 0xff, 0xff, 0xff, 0xff,
                           0xff, 0xff, 0xff, 0xff, 0xcf, 0xdf, 0xff});

    data_enc.insert(data_enc.end(), temp.begin(), temp.end());
  }

  PNG *out = new PNG(png->width(), png->height());

  int a = 0;
  for (int i = 0; i < png->width(); i++) {
    for (int j = 0; j < png->height(); j++) {
      RGBAPixel *pixel = out->getPixel(i, j);
      pixel->r = data_enc[a][0];
      pixel->g = data_enc[a][1];
      pixel->b = data_enc[a][2];
      pixel->a = (double)data_enc[a][3] / 255;
      a++;
    }
  }

  file_name = file_name.substr(0, file_name.find(".png")) + "_encrypted.png";
  cout << "Encryped File Saved to: " << file_name << endl;
  out->writeToFile(file_name);
}
