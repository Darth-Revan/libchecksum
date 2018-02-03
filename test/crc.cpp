/*
 * Copyright (c) 2018 Kevin Kirchner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @author      Kevin Kirchner
 * @date        2018
 * @copyright   MIT License
 * @brief       Test source file for tests of the checksums in \p libchecksum
 *
 * Source file containg test for CRCs in \p libchecksum.
 */


#include "catch.hpp"
#include <libchecksum/crc.h>

using namespace libchecksum;

// a vector of random test strings
const std::vector<std::string> TestVector {
    "5\"&l&7s:|In`'#kZiXA@[ee^^(kZ]Qp@",
    "p3S2`]Gt70",
    "D1='GdM'",
    "^*T@4|$!QD7",
    "qRbgfzdgDgkqF_-lC9TXl",
    "Rn5D61wB#,[\"n6s]zhp47s",
    "yG_0R{L)UX6Ow6mR",
    "[>",
    ""
};

TEST_CASE("Cksum") {
  Cksum crc;

  SECTION("generator") {
    REQUIRE(crc.getGeneratorPolynomial() == 0x04C11DB7);
  }

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"2e152bb1"};
    const uint32_t expected {773139377};
    REQUIRE(crc.getHex(str) == expectedHex);
    REQUIRE(crc(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};  // 010203042A51220C4C2217
    const std::string expectedHex {"11c09862"};
    const uint32_t expected {297834594};
    REQUIRE(crc.getHex(vec) == expectedHex);
    REQUIRE(crc(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(crc(TestVector[0]) == 1503098415);
    REQUIRE(crc(TestVector[1]) == 2690183564);
    REQUIRE(crc(TestVector[2]) == 93027024);
    REQUIRE(crc(TestVector[3]) == 1267458355);
    REQUIRE(crc(TestVector[4]) == 1602821092);
    REQUIRE(crc(TestVector[5]) == 1749922534);
    REQUIRE(crc(TestVector[6]) == 2673649835);
    REQUIRE(crc(TestVector[7]) == 3458002257);
    REQUIRE(crc(TestVector[8]) == 4294967295);
  }

}

TEST_CASE("CRC32") {
  CRC32 crc;

  SECTION("generator") {
    REQUIRE(crc.getGeneratorPolynomial() == 0xedb88320);
  }

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"4b8e39ef"};
    const uint32_t expected {1267612143};
    REQUIRE(crc.getHex(str) == expectedHex);
    REQUIRE(crc(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};  // 010203042A51220C4C2217
    const std::string expectedHex {"13124531"};
    const uint32_t expected {319964465};
    REQUIRE(crc.getHex(vec) == expectedHex);
    REQUIRE(crc(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(crc(TestVector[0]) == 558027374);
    REQUIRE(crc(TestVector[1]) == 3451413783);
    REQUIRE(crc(TestVector[2]) == 2753879460);
    REQUIRE(crc(TestVector[3]) == 1388732589);
    REQUIRE(crc(TestVector[4]) == 1520015303);
    REQUIRE(crc(TestVector[5]) == 1215597986);
    REQUIRE(crc(TestVector[6]) == 3899229996);
    REQUIRE(crc(TestVector[7]) == 3656879051);
    REQUIRE(crc(TestVector[8]) == 0);
  }
}
