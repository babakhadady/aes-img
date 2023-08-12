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
}
