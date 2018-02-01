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
 * @brief       Main source file for tests of \p libchecksum
 *
 * Main source file for the tests of \p libchecksum.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <libchecksum/checksums.h>

using namespace libchecksum;

TEST_CASE("convertSingleIntegerToHexString") {
  REQUIRE(util::toHexString(1234u) == "4d2");
  REQUIRE(util::toHexString(1234567890ull) == "499602d2");
  REQUIRE(util::toHexString(0u) == "0");
  REQUIRE(util::toHexString(-1u) == "ffffffff");
  REQUIRE(util::toHexString(-2u) == "fffffffe");
  uint8_t value {42};
  REQUIRE(util::toHexString(value) == "2a");
  uint16_t value2 {12345};
  REQUIRE(util::toHexString(value2) == "3039");
}

TEST_CASE("convertBytesVectorToHexString") {
  std::vector<uint8_t> Values {};
  REQUIRE(util::toHexString(Values).empty());
  Values.push_back(12);
  REQUIRE(util::toHexString(Values) == "0c");
  Values.push_back(255);
  REQUIRE(util::toHexString(Values) == "0cff");
  Values.clear();
  Values.push_back(128);
  Values.push_back(2);
  Values.push_back(static_cast<uint8_t>(-1u));
  REQUIRE(util::toHexString(Values) == "8002ff");
}

TEST_CASE("convertIntegerVectorToHexString") {
  std::vector<unsigned int> Values {};
  REQUIRE(util::toHexString(Values).empty());
  Values.push_back(12);
  REQUIRE(util::toHexString(Values) == "0000000c");
  Values.push_back(255);
  REQUIRE(util::toHexString(Values) == "0000000c000000ff");
  Values.clear();
  Values.push_back(128);
  Values.push_back(2);
  Values.push_back(static_cast<unsigned int>(-1u));
  REQUIRE(util::toHexString(Values) == "0000008000000002ffffffff");
}

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
    const std::vector<uint8_t> vec {1, 2, 3, 4, 42, 81, 34, 12, 76, 34, 23};
    const std::string expectedHex {"58a0139"};
    const uint32_t expected {92930361};
    REQUIRE(adler.getHex(vec) == expectedHex);
    REQUIRE(adler(vec) == expected);
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
}
