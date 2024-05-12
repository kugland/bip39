#include "../src/bip39.h"

#include <stdint.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <sodium.h>

#define TEST_BIP39(bits, lang, ...)                                    \
    {                                                                  \
        const char *expect[] = { __VA_ARGS__, NULL };                  \
        uint8_t entropy[bits / 8];                                     \
        for (unsigned i = 0; i < sizeof(entropy); i++) entropy[i] = i; \
        const char **mnemonic = bip39_mnemonic(bits, lang, entropy);   \
        CU_ASSERT_PTR_NOT_NULL(mnemonic);                              \
        if (mnemonic != NULL) {                                        \
            unsigned i = 0;                                            \
            do {                                                       \
                CU_ASSERT_STRING_EQUAL(mnemonic[i], expect[i]);        \
            } while (expect[++i] != NULL);                             \
            free(mnemonic);                                            \
        }                                                              \
    }

void
test__bip39(void)
{
    CU_ASSERT_NOT_EQUAL_FATAL(sodium_init(), -1);

    TEST_BIP39(128, "en", "abandon", "amount", "liar", "amount", "expire",
               "adjust", "cage", "candy", "arch", "gather", "drum", "buyer");
    TEST_BIP39(160, "en", "abandon", "amount", "liar", "amount", "expire",
               "adjust", "cage", "candy", "arch", "gather", "drum", "bullet",
               "absurd", "math", "exhibit");
    TEST_BIP39(192, "en", "abandon", "amount", "liar", "amount", "expire",
               "adjust", "cage", "candy", "arch", "gather", "drum", "bullet",
               "absurd", "math", "era", "live", "bid", "rib");
    TEST_BIP39(224, "en", "abandon", "amount", "liar", "amount", "expire",
               "adjust", "cage", "candy", "arch", "gather", "drum", "bullet",
               "absurd", "math", "era", "live", "bid", "rhythm", "alien",
               "crouch", "saddle");
    TEST_BIP39(256, "en", "abandon", "amount", "liar", "amount", "expire",
               "adjust", "cage", "candy", "arch", "gather", "drum", "bullet",
               "absurd", "math", "era", "live", "bid", "rhythm", "alien",
               "crouch", "range", "attend", "journey", "unaware");
    TEST_BIP39(128, "pt", "abacate", "afivelar", "inativo", "afivelar",
               "donzela", "achatar", "barulho", "beber", "albergue", "exalar",
               "cuidado", "banir");
    TEST_BIP39(160, "pt", "abacate", "afivelar", "inativo", "afivelar",
               "donzela", "achatar", "barulho", "beber", "albergue", "exalar",
               "cuidado", "baioneta", "abotoar", "joia", "divulgar");
    TEST_BIP39(192, "pt", "abacate", "afivelar", "inativo", "afivelar",
               "donzela", "achatar", "barulho", "beber", "albergue", "exalar",
               "cuidado", "baioneta", "abotoar", "joia", "dever", "informal",
               "argola", "penhasco");
    TEST_BIP39(224, "pt", "abacate", "afivelar", "inativo", "afivelar",
               "donzela", "achatar", "barulho", "beber", "albergue", "exalar",
               "cuidado", "baioneta", "abotoar", "joia", "dever", "informal",
               "argola", "peneira", "aditivo", "celebrar", "pivete");
    TEST_BIP39(256, "pt", "abacate", "afivelar", "inativo", "afivelar",
               "donzela", "achatar", "barulho", "beber", "albergue", "exalar",
               "cuidado", "baioneta", "abotoar", "joia", "dever", "informal",
               "argola", "peneira", "aditivo", "celebrar", "ouvido", "amarelo",
               "gritaria", "toalha");
}
