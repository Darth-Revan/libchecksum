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
 * @brief       Main header file of \p libchecksum
 *
 * This is the main header file declaring the library interface of
 * \p libchecksum.
 */

#ifndef LIBCHECKSUM_CHECKSUMS_H
#define LIBCHECKSUM_CHECKSUMS_H

#include <string>
#include <vector>

namespace libchecksum {

/// \brief Returns the current version of the library as string.
/// \return Library version as string
inline const std::string getVersionString() {
  return std::string{CHECKSUM_VERSION};
}

/// Class that implements the Adler32 checksum algorithm
class Adler32 final {

public:
  /// \brief Calculates the checksum of a byte vector.
  /// \param input Byte vector to get the checksum of
  /// \return Checksum of the byte vector
  uint32_t operator()(const std::vector<uint8_t>& input) const;

  /// \brief Calculates the checksum of a string.
  /// \param input String to get the checksum of
  /// \return Checksum of the string
  uint32_t operator()(const std::string& input) const;

  /// \brief Calculates the checksum of a byte vector and returns it in
  /// hexadecimal format.
  /// \param input Byte vector to get the checksum of
  /// \return Checksum of the byte vector as hexadecimal string
  std::string getHex(const std::vector<uint8_t>& input) const;

  /// \brief Calculates the checksum of a string and returns it in hexadecimal
  /// format.
  /// \param input String to get the checksum of
  /// \return Checksum of the string as hexadecimal string
  std::string getHex(const std::string& input) const;

};

} // namespace libchecksum

#endif //LIBCHECKSUM_CHECKSUMS_H
