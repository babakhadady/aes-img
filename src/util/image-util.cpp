#include "image-util.hpp"
#include "../aes.hpp"

PNG *ReadImage(string file_name)
{
  PNG *png = new PNG();
  png->readFromFile(file_name);
  return png;
}

void WriteImage(string file_name, vector<vector<uint8_t>> data_enc, PNG *png)
{
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

  file_name =
      "../out/" +
      file_name.substr(0, file_name.find(".png"))
          .substr(file_name.find_last_of("/") + 1, file_name.length() - 1) +
      "_encrypted.png";
  cout << "Encryped File Saved to: " << file_name << endl;
  out->writeToFile(file_name);
}

vector<vector<uint8_t>> ImageToVector(PNG *png)
{
  vector<vector<uint8_t>> data;

  for (int i = 0; i < png->width(); i++) {
    for (int j = 0; j < png->height(); j++) {
      RGBAPixel *pixel = png->getPixel(i, j);
      data.push_back(
          {pixel->r, pixel->g, pixel->b, (uint8_t)floor(pixel->a * 255)});
    }
  }

  /* Bit Padding */
  for (int i = 0; i < (png->width() * png->height() % 128); i++) {
    i == 0 ? data.push_back({0x80, 0x00, 0x00, 0x00})
           : data.push_back({0x00, 0x00, 0x00, 0x00});
  }

  return data;
}

vector<vector<uint8_t>> EncryptImage(vector<vector<uint8_t>> data, vector<uint8_t> key)
{
  AES *aes = new AES();
  vector<vector<uint8_t>> data_enc;
  vector<vector<uint8_t>> prev;

  for (int i = 0; i < data.size(); i += 4) {
    vector<vector<uint8_t>> temp{data[i], data[i + 1], data[i + 2],
                                 data[i + 3]};

    i != 0 ? aes->AddCipherText(temp, prev)
           : aes->AddInitializationVector(temp);

    aes->AesEncrypt(temp, key);

    data_enc.insert(data_enc.end(), temp.begin(), temp.end());
    prev = temp;
  }
	return data_enc;
}
