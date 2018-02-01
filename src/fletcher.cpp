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
 * @brief       Implements the Fletcher checksum algorithms
 *
 * This source file implements the Fletcher checksum algorithms declared in the
 * main header.
 */

#include <libchecksum/checksums.h>

namespace libchecksum {

uint16_t Fletcher16::operator()(const std::string& input) const {
  return this->operator()(std::vector<uint8_t> {input.begin(), input.end()});
}

uint16_t Fletcher16::operator()(const std::vector<uint8_t>& input) const {
  uint16_t s1 {0}, s2 {0};
  for (const auto& element : input) {
    s1 = static_cast<uint16_t>((s1 + element) % 255);
    s2 = static_cast<uint16_t>((s2 + s1) % 255);
  }
  return static_cast<uint16_t>((s2 << 8) | s1);
}

uint32_t Fletcher32::operator()(const std::string& input) const {
  return this->operator()(std::vector<uint8_t> {input.begin(), input.end()});
}

uint32_t Fletcher32::operator()(const std::vector<uint8_t>& input) const {
  uint32_t s1 {0}, s2 {0};
  for (const auto& element : input) {
    s1 = (s1 + element) % 65535;
    s2 = (s2 + s1) % 65535;
  }
  return (s2 << 16) | s1;
}

}