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
 * @brief       Implements checksum algorithms
 *
 * This source file implements checksum algorithms declared in the main header.
 */

#include <libchecksum/checksums.h>

namespace libchecksum {

uint32_t Adler32::operator()(const std::vector<uint8_t>& input) const {
  uint32_t s1 {1}, s2 {0};
  for (const auto& element : input) {
    s1 = (s1 + element) % 65521;
    s2 = (s2 + s1) % 65521;
  }
  return (s2 << 16) | s1;
}

uint16_t Fletcher16::operator()(const std::vector<uint8_t>& input) const {
  uint16_t s1 {0}, s2 {0};
  for (const auto& element : input) {
    s1 = static_cast<uint16_t>((s1 + element) % 255);
    s2 = static_cast<uint16_t>((s2 + s1) % 255);
  }
  return static_cast<uint16_t>((s2 << 8) | s1);
}

uint32_t Fletcher32::operator()(const std::vector<uint8_t>& input) const {
  uint32_t s1 {0}, s2 {0};
  for (const auto& element : input) {
    s1 = (s1 + element) % 65535;
    s2 = (s2 + s1) % 65535;
  }
  return (s2 << 16) | s1;
}

uint8_t Sum8::operator()(const std::vector<uint8_t>& input) const {
  uint8_t checksum {0};
  for (const auto& byte : input) {
    checksum = static_cast<uint8_t>((checksum + byte) & 0xFF);
  }
  return checksum;
}

uint16_t Sum16::operator()(const std::vector<uint8_t>& input) const {
  uint16_t checksum {0};
  for (const auto& byte : input) {
    checksum = static_cast<uint16_t>((checksum + byte) & 0xFFFF);
  }
  return checksum;
}

uint32_t Sum32::operator()(const std::vector<uint8_t>& input) const {
  uint32_t checksum {0};
  for (const auto& byte : input) {
    checksum = (checksum + byte) & 0xFFFFFF;
  }
  return checksum;
}

uint16_t BSDSum::operator()(const std::vector<uint8_t>& input) const {
  uint16_t checksum {0};
  for (const auto& byte : input) {
    checksum = static_cast<uint16_t>((checksum >> 1) + ((checksum & 1) << 15));
    checksum += byte;
    checksum &= 0xFFFF;
  }
  return checksum;
}

uint8_t XOR8::operator()(const std::vector<uint8_t>& input) const {
  uint8_t checksum {0};
  for (const auto& byte : input) {
    checksum ^= byte & 0xFF;
  }
  return checksum;
}

uint32_t SYSV::operator()(const std::vector<uint8_t>& input) const {
  uint32_t s {0}, r {0};
  for (const auto& byte : input) {
    s += byte;
  }
  r = (s & 0xFFFF) + ((s & 0xFFFFFFFF) >> 16);
  return (r & 0xFFFF) + (r >> 16);
}

}
