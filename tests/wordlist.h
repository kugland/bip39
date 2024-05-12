#include "../src/wordlist.h"

#include <CUnit/Basic.h>

void
test__wordlist(void)
{
    const wordlist_t *w;

    {
        for (w = wordlists; w->lang != NULL; w++) {
            /* If the wordlist is not NULL, the words should not be NULL */
            CU_ASSERT_PTR_NOT_NULL(w->words);

            if (w->words != NULL) {
                /* Check each list has exactly 2048 words */
                const char *words = w->words;
                for (int i = 0; i < 2048; i++) {
                    CU_ASSERT_TRUE(strlen(words) > 0);
                    words += strlen(words) + 1;
                }
                CU_ASSERT_TRUE(strlen(words) == 0);
            }
        }

        /* The last wordlist should be {NULL, NULL} */
        CU_ASSERT_PTR_NULL(w->lang);
        CU_ASSERT_PTR_NULL(w->words);
    }

    {
        /* Check that the index can be built for each language */
        for (w = wordlists; w->lang != NULL; w++) {
            const char *index[2048];
            CU_ASSERT_TRUE(wordlist_get_index(w->lang, index));
            for (int i = 0; i < 2048; i++) {
                CU_ASSERT_PTR_NOT_NULL(index[i]);
            }
        }
    }

    {
        /* Check that building the index for an unknown language fails */
        const char *index[2048];
        CU_ASSERT_FALSE(wordlist_get_index("unknown", index));
    }
}
