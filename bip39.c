#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <sodium.h>

#include "wordlist.cs.h"
#include "wordlist.en.h"
#include "wordlist.es.h"
#include "wordlist.fr.h"
#include "wordlist.it.h"
#include "wordlist.ja.h"
#include "wordlist.ko.h"
#include "wordlist.pt.h"
#include "wordlist.zh_cn.h"
#include "wordlist.zh_tw.h"

#define BITS_TO_BYTES(x) (((x) + 7) >> 3)
#define BYTES_TO_BITS(x) ((x) << 3)
#define SUFFIX_BITS(x) ((x) >> 5)
#define TOTAL_BITS(x) ((x) + SUFFIX_BITS(x))
#define NUM_WORDS(x) ((TOTAL_BITS(x)) / 11)

char *to_binary(const void *data, size_t no_of_bits)
{
  const char* data_ptr = data;
  char* bits = malloc(no_of_bits + 1);
  for (size_t i = 0; i < no_of_bits; i++) {
    bits[i] = ((data_ptr[i >> 3] >> (7 - (i & 7))) & 1) ? '1' : '0';
  }
  bits[no_of_bits + 1] = '\0';
  return bits;
}

void help(void) {
  (void) system("man 1 bip39");
}

int main(int argc, char *argv[])
{
  if (argc < 2 || argc > 3) {
    help();
    return 1;
  }

  size_t no_of_bits;

  no_of_bits = atoi(argv[1]);

  switch (no_of_bits) {
    case 128:
    case 160:
    case 192:
    case 224:
    case 256: break;
    default:
      help();
      return 1;
  }

  char* language = argv[2];
  const char** wordlist = wordlists_english;

  if (argc == 3) {
    if (strcmp(language, "en") == 0) {
      wordlist = wordlists_english;
    } else if (strcmp(language, "fr") == 0) {
      wordlist = wordlists_french;
    } else if (strcmp(language, "es") == 0) {
      wordlist = wordlists_spanish;
    } else if (strcmp(language, "pt") == 0) {
      wordlist = wordlists_portuguese;
    } else if (strcmp(language, "it") == 0) {
      wordlist = wordlists_italian;
    } else if (strcmp(language, "cs") == 0) {
      wordlist = wordlists_czech;
    } else if (strcmp(language, "ko") == 0) {
      wordlist = wordlists_korean;
    } else if (strcmp(language, "ja") == 0) {
      wordlist = wordlists_japanese;
    } else if (strcmp(language, "zh_tw") == 0) {
      wordlist = wordlists_chinese_traditional;
    } else if (strcmp(language, "zh_cn") == 0) {
      wordlist = wordlists_chinese_simplified;
    } else {
      help();
      return 1;
    }
  }

  /* Get entropy. */
  unsigned char *entropy = malloc(BITS_TO_BYTES(no_of_bits));
  randombytes_buf(entropy, BITS_TO_BYTES(no_of_bits));
  char *entropy_bits = to_binary(entropy, no_of_bits);

  /* Compute SHA256 hash of entropy. */
  unsigned char sha256_hash[crypto_hash_sha256_BYTES];
  crypto_hash_sha256(sha256_hash, entropy, BITS_TO_BYTES(no_of_bits));
  char *hash_bits = to_binary(sha256_hash, BYTES_TO_BITS(crypto_hash_sha256_BYTES));

  /* Realloc to fit the suffix. */
  entropy_bits = realloc(entropy_bits, TOTAL_BITS(no_of_bits) + 1);

  /* Copy the suffix. */
  memcpy(entropy_bits + no_of_bits, hash_bits, SUFFIX_BITS(no_of_bits));
  entropy_bits[TOTAL_BITS(no_of_bits)] = '\0';

  /* Select and print the words. */
  for (size_t i = 0; i < NUM_WORDS(no_of_bits); i++) {
    uint16_t index = 0;
    for (size_t bit = 0; bit < 11; bit++) {
      index <<= 1;
      index |= (entropy_bits[i * 11 + bit] == '1');
    }
    printf("%s%c", wordlist[index], (i == NUM_WORDS(no_of_bits) - 1) ? '\n' : ' ');
  }

  /* Overwrite generated data. */
  memset(entropy, 0, BITS_TO_BYTES(no_of_bits));
  memset(sha256_hash, 0, crypto_hash_sha256_BYTES);
  memset(entropy_bits, 0, TOTAL_BITS(no_of_bits) + 1);
  memset(hash_bits, 0, BYTES_TO_BITS(crypto_hash_sha256_BYTES));

  /* Free the allocated memory. */
  free(entropy);
  free(entropy_bits);
  free(hash_bits);

  return 0;
}
