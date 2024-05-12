#include "bip39.h"
#include "bits.h"
#include "opts.h"
#include "wordlist.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#define ADD_TEST(name)                                    \
    if (CU_add_test(pSuite, #name, test__##name) == NULL) \
        goto finish;

int
main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("bip39", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    ADD_TEST(opts);
    ADD_TEST(bits);
    ADD_TEST(wordlist);
    ADD_TEST(bip39);

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

finish:
    CU_cleanup_registry();
    return CU_get_error();
}
