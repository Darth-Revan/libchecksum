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
#include <libchecksum/common.h>

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
