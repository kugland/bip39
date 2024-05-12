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

#ifndef BIP39_BIP39_H
#define BIP39_BIP39_H

#include <stdint.h>
#include <stdlib.h>

/**

    @brief Generate a BIP-0039 mnemonic phrase.

    This function generates a BIP-0039 mnemonic phrase from a given entropy
    value, or generates a new entropy value if none is provided.

    @param ent_bits The number of bits of entropy to use.
    @param lang     The language of the wordlist to use.
    @param ent      A pointer to the entropy value to use, or NULL to generate
                    a new entropy value. If provided, the entropy value must
                    be ent_bits bits long.

    @return A pointer to the generated mnemonic phrase, or NULL if an error
            occurred. The caller is responsible for freeing the memory.

*/
const char **bip39_mnemonic(size_t ent_bits, const char *lang,
                            const uint8_t *ent);

#endif /* BIP39_BIP39_H */
