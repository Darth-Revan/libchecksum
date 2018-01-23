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
 * @bug         No known bugs
 * @brief       Declares classes and functions
 *
 * This header file declares classes and functions that implement the library
 * functionality.
 */

#ifndef CHECKSUM_ABSTRACT_H
#define CHECKSUM_ABSTRACT_H

#include <vector>
#include <sstream>
#include <iomanip>

namespace libchecksum {

namespace util {

/// \brief Template function to convert an integral value to a hexadecimal
/// string.
///
/// Does only compile for unsigned integral values (e.g. unsigned int,
/// uint8_t, unsigned char, ...). This function does not pad the hexadecimal
/// string with zeroes.
/// \tparam INTTYPE Type of the input value
/// \param value Value to convert to hex
/// \return The input value as hexadecimal string
template <typename INTTYPE>
std::string toHexString(INTTYPE value) {
  static_assert(std::is_integral<INTTYPE>::value, "This template can only be used for integer types!");
  static_assert(std::is_unsigned<INTTYPE>::value, "This template can only be used for unsigned values!");

  std::stringstream stream {""};
  stream << std::hex << +value;
  return stream.str();
}

/// \brief Template function to convert a vector of integral values to a
/// hexadecimal string.
///
/// Does only compile for vectors of unsigned integral values (e.g. unsigned int,
/// uint8_t, unsigned char, ...). The function converts each value separately,
/// pads them to twice their byte size (e.g. uint8_t will be padded to 2
/// characters) and simply concatenates them.
/// \tparam INTTYPE Type of the input values
/// \param values Vector of values to convert to hex
/// \return The input values as hexadecimal string
template<typename INTTYPE>
std::string toHexString(const std::vector<INTTYPE>& values) {
  static_assert(std::is_integral<INTTYPE>::value, "This template can only be used for vectors of integer types!");
  static_assert(std::is_unsigned<INTTYPE>::value, "This template can only be used for vectors of unsigned values!");

  std::stringstream stream {""};
  for (const INTTYPE& value : values) {
    stream << std::hex << std::setfill('0') << std::setw(sizeof(INTTYPE) * 2) << +value;
  }
  return stream.str();
}

} // namespace util

}

#endif //CHECKSUM_ABSTRACT_H
