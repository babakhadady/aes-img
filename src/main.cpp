#include "./util/image-util.hpp"
#include "aes.hpp"
#include <iostream>
#include <string>

const vector<uint8_t> key = {0xff, 0xff, 0xff, 0xaf, 0xbf, 0xff, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xdf, 0xff};

int main(int argc, char *argv[])
{

  if (argc == 1) {
    printf("Specify a File to Encrypt\n");
    return -1;
  }
  std::string file_name = argv[1];

  std::cout << "File to Encrypt: " << file_name << std::endl;

  PNG *png = ReadImage(file_name);

	vector<vector<uint8_t>> data = ImageToVector(png);
  vector<vector<uint8_t>> data_enc = EncryptImage(data, key);
  vector<vector<uint8_t>> prev;

	WriteImage(file_name, data_enc, png);

}
