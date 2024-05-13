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

#include "bip39.h"
#include "bits.h"
#include "opts.h"
#include "wordlist.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>

const char **
bip39_mnemonic(size_t ent_bits, const char *lang, const uint8_t *ent)
{
    const int ent_bytes = ent_bits >> 3;
    const int cs_bits = ent_bits >> 5;
    const int entcs_bits = ent_bits + cs_bits;
    const int entcs_bytes = (entcs_bits + 7) >> 3;
    const int mnemonic_len = entcs_bits / 11;

    /* Allocate all the memory we need, so we can fail fast in case of
       allocation failure */
    const char *words[2048] = { 0 };
    if (!wordlist_get_index(lang, words))
        return NULL;
    uint8_t *entcs = sodium_malloc(entcs_bytes);
    const char **mnemonic = sodium_allocarray(mnemonic_len + 1, sizeof(char *));
    if (entcs == NULL || mnemonic == NULL) {
        sodium_free(entcs);
        sodium_free(mnemonic);
        return NULL;
    }

    /* If entropy is not provided, generate a new random value, otherwise
       copy the provided value */
    if (ent == NULL) {
        randombytes_buf(entcs, ent_bytes);
    } else {
        memcpy(entcs, ent, ent_bytes);
    }

    /* Calculate the checksum (first cs_bits of the hash of the entropy), and
       append it to entcs */
    uint8_t hash[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(hash, entcs, ent_bytes);
    uintmax_t cs = bits_get(0, cs_bits, hash);
    bits_set(ent_bits, cs_bits, entcs, cs);

    /* Build the mnemonic phrase */
    for (int i = 0; i < mnemonic_len; i++) {
        uintmax_t idx = bits_get(i * 11, 11, entcs);
        mnemonic[i] = words[idx];
    }
    mnemonic[mnemonic_len] = NULL;

    /* Zero out sensitive data and free memory */
    sodium_memzero(hash, crypto_hash_sha256_BYTES);
    sodium_memzero(&cs, sizeof(cs));
    sodium_free(entcs);

    return mnemonic;
}
