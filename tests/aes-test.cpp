#include "../lib/Catch2/catch.hpp"
#include "../src/aes.hpp"


TEST_CASE("ShiftRows shifts rows correctly", "[aes]")
{
  SBox* sbox = new SBox();
	vector<vector<uint8_t>> test =  
  for (int i = 0; i < 256; i++) {
    actual = i;
    sbox->ForwardSBox(&actual);
    REQUIRE(REFERENCE_SBOX[i] == actual);
  }
}
