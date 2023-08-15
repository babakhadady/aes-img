#include "../lib/Catch2/catch.hpp"
#include "../src/aes.hpp"

TEST_CASE("Testing AES helper functions", "[aes]")
{

  AES *aes = new AES();
  SECTION("ShiftRows shifts rows correctly")
  {
    vector<vector<uint8_t>> test_array{{1, 2, 3, 4},
                                       {5, 6, 7, 8},
                                       {9, 10, 11, 12},
                                       {13, 14, 15, 16},
                                       {17, 18, 19, 20}};

    vector<vector<uint8_t>> actual{{1, 2, 3, 4},
                                   {6, 7, 8, 5},
                                   {11, 12, 9, 10},
                                   {16, 13, 14, 15},
                                   {17, 18, 19, 20}};

    aes->ShiftRows(test_array);
    for (int i = 0; i < test_array.size(); i++) {
      for (int j = 0; j < test_array[i].size(); j++) {
        REQUIRE(test_array[i][j] == actual[i][j]);
      }
    }
  }

  SECTION("MixColumns properly mixes columns")
  {
    vector<vector<uint8_t>> test_array{{219, 242, 1, 198, 212, 45},
                                       {19, 10, 1, 198, 212, 38},
                                       {83, 34, 1, 198, 212, 49},
                                       {69, 92, 1, 198, 213, 76}};
    vector<vector<uint8_t>> actual{{142, 159, 1, 198, 213, 77},
                                   {77, 220, 1, 198, 213, 126},
                                   {161, 88, 1, 198, 215, 189},
                                   {188, 157, 1, 198, 214, 248}};
    aes->MixColumns(test_array);
    for (int i = 0; i < test_array.size(); i++) {
      for (int j = 0; j < test_array[i].size(); j++) {
        REQUIRE(test_array[i][j] == actual[i][j]);
      }
    }
  }

  SECTION("NextRoundKey properly generates each round key for 128 bit key")
  {

    vector<vector<vector<uint8_t>>> test_keys = {{{0x49, 0x20, 0xe2, 0x99},
                                                   {0xa5, 0x20, 0x52, 0x61},
                                                   {0x64, 0x69, 0x6f, 0x47},
                                                   {0x61, 0x74, 0x75, 0x6e}},

                                                  {{0x00, 0x01, 0x02, 0x03},
                                                   {0x04, 0x05, 0x06, 0x07},
                                                   {0x08, 0x09, 0x0a, 0x0b},
                                                   {0x0c, 0x0d, 0x0e, 0x0f}},

                                                  {{0xff, 0xff, 0xff, 0xff},
                                                   {0xff, 0xff, 0xff, 0xff},
                                                   {0xff, 0xff, 0xff, 0xff},
                                                   {0xff, 0xff, 0xff, 0xff}},

                                                  {{0x00, 0x00, 0x00, 0x00},
                                                   {0x00, 0x00, 0x00, 0x00},
                                                   {0x00, 0x00, 0x00, 0x00},
                                                   {0x00, 0x00, 0x00, 0x00}}};

		for (auto key : test_keys) {
			vector<vector<uint8_t>> prev_key = key;
			for (int i = 1; i <= 10; i++) {

			}
		}
  }
}
