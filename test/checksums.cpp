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
 * Source file containg test for checksums in \p libchecksum.
 */

#include "catch.hpp"
#include <libchecksum/checksums.h>

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

TEST_CASE("Adler32") {
  Adler32 adler;

  SECTION("string") {
    const std::string str {"Test String Adler32"};
    const std::string expectedHex {"451d06a5"};
    const uint32_t expected {1159530149};
    REQUIRE(adler.getHex(str) == expectedHex);
    REQUIRE(adler(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};  // 010203042A51220C4C2217
    const std::string expectedHex {"58a0139"};
    const uint32_t expected {92930361};
    REQUIRE(adler.getHex(vec) == expectedHex);
    REQUIRE(adler(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(adler(TestVector[0]) == 2612464132);
    REQUIRE(adler(TestVector[1]) == 290587400);
    REQUIRE(adler(TestVector[2]) == 146342393);
    REQUIRE(adler(TestVector[3]) == 300614366);
    REQUIRE(adler(TestVector[4]) == 1458636689);
    REQUIRE(adler(TestVector[5]) == 1242105546);
    REQUIRE(adler(TestVector[6]) == 746456368);
    REQUIRE(adler(TestVector[7]) == 16122010);
    REQUIRE(adler(TestVector[8]) == 1);
  }
}

TEST_CASE("Fletcher16") {
  Fletcher16 fletcher;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"2057"};
    const uint16_t expected {8279};
    REQUIRE(fletcher.getHex(str) == expectedHex);
    REQUIRE(fletcher(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"8439"};
    const uint16_t expected {33849};
    REQUIRE(fletcher.getHex(vec) == expectedHex);
    REQUIRE(fletcher(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(fletcher(TestVector[0]) == 13069);
    REQUIRE(fletcher(TestVector[1]) == 22794);
    REQUIRE(fletcher(TestVector[2]) == 47609);
    REQUIRE(fletcher(TestVector[3]) == 61919);
    REQUIRE(fletcher(TestVector[4]) == 13207);
    REQUIRE(fletcher(TestVector[5]) == 15823);
    REQUIRE(fletcher(TestVector[6]) == 39476);
    REQUIRE(fletcher(TestVector[7]) == 62617);
    REQUIRE(fletcher(TestVector[8]) == 0);
  }
}

TEST_CASE("Fletcher32") {
  Fletcher32 fletcher;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"8180255"};
    const uint32_t expected {135791189};
    REQUIRE(fletcher.getHex(str) == expectedHex);
    REQUIRE(fletcher(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"57f0138"};
    const uint32_t expected {92209464};
    REQUIRE(fletcher.getHex(vec) == expectedHex);
    REQUIRE(fletcher(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(fletcher(TestVector[0]) == 2610366979);
    REQUIRE(fletcher(TestVector[1]) == 289932039);
    REQUIRE(fletcher(TestVector[2]) == 145818104);
    REQUIRE(fletcher(TestVector[3]) == 299893469);
    REQUIRE(fletcher(TestVector[4]) == 1457260432);
    REQUIRE(fletcher(TestVector[5]) == 1240663753);
    REQUIRE(fletcher(TestVector[6]) == 745407791);
    REQUIRE(fletcher(TestVector[7]) == 15990937);
    REQUIRE(fletcher(TestVector[8]) == 0);
  }
}

TEST_CASE("Sum8") {
  Sum8 sum;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"55"};
    const uint8_t expected {85};
    REQUIRE(sum.getHex(str) == expectedHex);
    REQUIRE(sum(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"38"};
    const uint8_t expected {56};
    REQUIRE(sum.getHex(vec) == expectedHex);
    REQUIRE(sum(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(sum(TestVector[0]) == 3);
    REQUIRE(sum(TestVector[1]) == 7);
    REQUIRE(sum(TestVector[2]) == 248);
    REQUIRE(sum(TestVector[3]) == 221);
    REQUIRE(sum(TestVector[4]) == 144);
    REQUIRE(sum(TestVector[5]) == 201);
    REQUIRE(sum(TestVector[6]) == 47);
    REQUIRE(sum(TestVector[7]) == 153);
    REQUIRE(sum(TestVector[8]) == 0);
  }
}

TEST_CASE("Sum16") {
  Sum16 sum;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"255"};
    const uint16_t expected {597};
    REQUIRE(sum.getHex(str) == expectedHex);
    REQUIRE(sum(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"138"};
    const uint16_t expected {312};
    REQUIRE(sum.getHex(vec) == expectedHex);
    REQUIRE(sum(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(sum(TestVector[0]) == 2563);
    REQUIRE(sum(TestVector[1]) == 775);
    REQUIRE(sum(TestVector[2]) == 504);
    REQUIRE(sum(TestVector[3]) == 733);
    REQUIRE(sum(TestVector[4]) == 1936);
    REQUIRE(sum(TestVector[5]) == 1737);
    REQUIRE(sum(TestVector[6]) == 1327);
    REQUIRE(sum(TestVector[7]) == 153);
    REQUIRE(sum(TestVector[8]) == 0);
  }
}

TEST_CASE("Sum32") {
  Sum32 sum;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"255"};
    const uint32_t expected {597};
    REQUIRE(sum.getHex(str) == expectedHex);
    REQUIRE(sum(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"138"};
    const uint32_t expected {312};
    REQUIRE(sum.getHex(vec) == expectedHex);
    REQUIRE(sum(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(sum(TestVector[0]) == 2563);
    REQUIRE(sum(TestVector[1]) == 775);
    REQUIRE(sum(TestVector[2]) == 504);
    REQUIRE(sum(TestVector[3]) == 733);
    REQUIRE(sum(TestVector[4]) == 1936);
    REQUIRE(sum(TestVector[5]) == 1737);
    REQUIRE(sum(TestVector[6]) == 1327);
    REQUIRE(sum(TestVector[7]) == 153);
    REQUIRE(sum(TestVector[8]) == 0);
  }
}

TEST_CASE("BSDSum") {
  BSDSum sum;

  SECTION("string") {
    const std::string str {"abcdef"};
    const std::string expectedHex {"8c7"};
    const uint16_t expected {2247};
    REQUIRE(sum.getHex(str) == expectedHex);
    REQUIRE(sum(str) == expected);
  }

  SECTION("bytes") {
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"dc81"};
    const uint16_t expected {56449};
    REQUIRE(sum.getHex(vec) == expectedHex);
    REQUIRE(sum(vec) == expected);
  }

  SECTION("testvector") {
    REQUIRE(sum(TestVector[0]) == 11656);
    REQUIRE(sum(TestVector[1]) == 2428);
    REQUIRE(sum(TestVector[2]) == 1141);
    REQUIRE(sum(TestVector[3]) == 20729);
    REQUIRE(sum(TestVector[4]) == 9117);
    REQUIRE(sum(TestVector[5]) == 49617);
    REQUIRE(sum(TestVector[6]) == 2740);
    REQUIRE(sum(TestVector[7]) == 32875);
    REQUIRE(sum(TestVector[8]) == 0);
  }
}
