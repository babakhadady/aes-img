#ifndef image_util
#define image_util

#include "../../lib/cs221util/PNG.h"

using namespace cs221util;

PNG *ReadImage(string file_name);
void WriteImage(string file_name, vector<vector<uint8_t>> data_enc, PNG *png);
vector<vector<uint8_t>> ImageToVector(PNG *png);
vector<vector<uint8_t>> EncryptImage(vector<vector<uint8_t>> data,
                                     vector<uint8_t> key);

#endif
