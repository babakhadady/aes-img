#include "../lib/Catch2/catch.hpp"
#include "../src/aes.hpp"

TEST_CASE("ShiftRows shifts rows correctly", "[aes]")
{
	AES* aes = new AES();
  vector<vector<uint8_t>> test{{1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16},
                               {17, 18, 19, 20}};

  vector<vector<uint8_t>> actual{{1, 2, 3, 4},
                                 {6, 7, 8, 5},
                                 {11, 12, 9, 10},
                                 {16, 13, 14, 15},
                                 {17, 18, 19, 20}};

	
	aes->ShiftRows(test);
  for (int i = 0; i < test.size(); i++) {
    for (int j = 0; j < test[i].size(); j++) {
      REQUIRE(test[i][j] == actual[i][j]);
    }
  }
}
