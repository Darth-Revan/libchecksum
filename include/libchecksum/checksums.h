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
 * @brief       Main header file of \p libchecksum
 *
 * This is the main header file declaring the library interface of
 * \p libchecksum.
 */

#ifndef LIBCHECKSUM_CHECKSUMS_H
#define LIBCHECKSUM_CHECKSUMS_H

#include <string>
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

/// \brief Returns the current version of the library as string.
/// \return Library version as string
inline const std::string getVersionString() {
  return std::string{CHECKSUM_VERSION};
}

/// Abstract class for checksum algorithms
template<typename T>
class ChecksumAlgorithm {
  static_assert(std::is_integral<T>::value, "This class can only be used for integral types!");

public:
  /// \brief Default virtual destructor
  virtual ~ChecksumAlgorithm() = default;

  /// \brief Calculates the checksum of a byte vector.
  /// \param input Byte vector to get the checksum of
  /// \return Checksum of the byte vector
  virtual T operator()(const std::vector<uint8_t>& input) const = 0;

  /// \brief Calculates the checksum of a string.
  /// \param input String to get the checksum of
  /// \return Checksum of the string
  virtual T operator()(const std::string& input) const = 0;

  /// \brief Calculates the checksum of a byte vector and returns it in
  /// hexadecimal format.
  /// \param input Byte vector to get the checksum of
  /// \return Checksum of the byte vector as hexadecimal string
  virtual const std::string getHex(const std::vector<uint8_t>& input) const final {
    return util::toHexString((*this) (input));
  }

  /// \brief Calculates the checksum of a string and returns it in hexadecimal
  /// format.
  /// \param input String to get the checksum of
  /// \return Checksum of the string as hexadecimal string
  virtual const std::string getHex(const std::string& input) const final {
    return util::toHexString((*this) (input));
  }

};

/// Class that implements the Adler32 checksum algorithm
class Adler32 final : public ChecksumAlgorithm<uint32_t> {

public:
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
  uint32_t operator()(const std::string& input) const override;
};

/// Class that implements the Fletcher16 checksum algorithm
class Fletcher16 final : public ChecksumAlgorithm<uint16_t> {

public:
  uint16_t operator()(const std::vector<uint8_t>& input) const override;
  uint16_t operator()(const std::string& input) const override;
};

/// Class that implements the Fletcher32 checksum algorithm
class Fletcher32 final : public ChecksumAlgorithm<uint32_t> {

public:
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
  uint32_t operator()(const std::string& input) const override;
};

} // namespace libchecksum

#endif //LIBCHECKSUM_CHECKSUMS_H
