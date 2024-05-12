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

#include "bits.h"

#include <assert.h>
#include <stdint.h>
#include <endian.h>

uintmax_t
bits_get(int start, int count, const uint8_t *bits)
{
    assert((unsigned)count <= (sizeof(uintmax_t) << 3));

    uintmax_t value = 0;

    bits += start >> 3;
    start &= 7;

    for (int i = start; i < (start + count); i++) {
        const int byte = i >> 3;
        const int shift = 7 - (i & 7);
        value <<= 1;
        value |= (bits[byte] >> shift) & 1;
    }

    return value;
}

void
bits_set(int start, int count, uint8_t *bits, uintmax_t value)
{
    assert((unsigned)count <= (sizeof(uintmax_t) << 3));

    bits += start >> 3;
    start &= 7;

    for (int i = start + count - 1; i >= start; i--) {
        const int byte = i >> 3;
        const int shift = 7 - (i & 7);
        bits[byte] &= ~(1 << shift);
        bits[byte] |= (value & 1) << shift;
        value >>= 1;
    }
}
