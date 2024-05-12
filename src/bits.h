/*

Copyright (c) 2021-2024 André Kugland

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef BIPS39_BITS_H
#define BIPS39_BITS_H

#include <stdint.h>

/**

    @brief Extract bits from a byte array.

    This function extracts a specified range of bits from a byte array and
    combines them into a uintmax_t value.

    @param start  The starting bit position within the byte array (0-based).
    @param count  The number of consecutive bits to extract.
    @param bits   A pointer to the byte array containing the bits.

    @return The extracted bits as a uintmax_t value.

*/
uintmax_t bits_get(int start, int count, const uint8_t *bits);

/**

    @brief Set a range of bits within a byte array.

    This function sets a specified range of bits within a byte array to the
    value provided in the least significant bits of a uintmax_t value.

    @param start  The starting bit position within the byte array (0-based).
    @param count  The number of consecutive bits to set.
    @param bits   A pointer to the byte array containing the bits.
    @param value  The value containing the bits to be set.

*/
void bits_set(int start, int count, uint8_t *bits, uintmax_t value);

#endif /* BIPS39_BITS_H */
