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
 * @brief       Header file of \p libchecksum declaring checksum algorithms
 *
 * This header file declares the checksum algorithms of \p libchecksum.
 */

#ifndef LIBCHECKSUM_CHECKSUMS_H
#define LIBCHECKSUM_CHECKSUMS_H

#include <libchecksum/common.h>

namespace libchecksum {

/// Class that implements the Adler32 checksum algorithm
class Adler32 final : public ChecksumAlgorithm<uint32_t> {

public:
  using ChecksumAlgorithm::operator();
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the Fletcher16 checksum algorithm
class Fletcher16 final : public ChecksumAlgorithm<uint16_t> {

public:
  using ChecksumAlgorithm::operator();
  uint16_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the Fletcher32 checksum algorithm
class Fletcher32 final : public ChecksumAlgorithm<uint32_t> {

public:
  using ChecksumAlgorithm::operator();
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements a 8 bit checksum
class Sum8 final : public ChecksumAlgorithm<uint8_t> {

public:
  using ChecksumAlgorithm::operator();
  uint8_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements a 16 bit checksum
class Sum16 final : public ChecksumAlgorithm<uint16_t> {

public:
  using ChecksumAlgorithm::operator();
  uint16_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements a 32 bit checksum
class Sum32 final : public ChecksumAlgorithm<uint32_t> {

public:
  using ChecksumAlgorithm::operator();
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the 16 bit long BSD sum
class BSDSum final : public ChecksumAlgorithm<uint16_t> {

public:
  using ChecksumAlgorithm::operator();
  uint16_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the XOR8 checksum
class XOR8 final : public ChecksumAlgorithm<uint8_t> {

public:
  using ChecksumAlgorithm::operator();
  uint8_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the SYSV checksum
class SYSV final : public ChecksumAlgorithm<uint32_t> {

public:
  using ChecksumAlgorithm::operator();
  uint32_t operator()(const std::vector<uint8_t>& input) const override;
};

/// Class that implements the CRC checksum from the GNU coreutil cksum
class Cksum final : public CyclicRedundancyChecksum<uint32_t> {

public:
  using ChecksumAlgorithm::operator();
  uint32_t operator()(const std::vector<uint8_t>& input) const override;

  uint32_t getGeneratorPolynomial() const override {
    return 0x04C11DB7;
  }
};

} // namespace libchecksum

#endif //LIBCHECKSUM_CHECKSUMS_H
