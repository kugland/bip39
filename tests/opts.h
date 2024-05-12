#include "../src/opts.h"

#include <CUnit/Basic.h>

#define TEST_BITS(x)                                                    \
    {                                                                   \
        opts_t opts;                                                    \
        opts_from_cmdline(3, (char *[]) { "bips39", "-b", #x }, &opts); \
        CU_ASSERT_EQUAL(opts.bits, x);                                  \
    }

#define TEST_LANG(x)                                                   \
    {                                                                  \
        opts_t opts;                                                   \
        opts_from_cmdline(3, (char *[]) { "bips39", "-l", x }, &opts); \
        CU_ASSERT_STRING_EQUAL(opts.lang, x);                          \
    }

void
test__opts(void)
{
    opts_t opts;

    opts_from_cmdline(1, (char *[]) { "bips39" }, &opts);
    CU_ASSERT_EQUAL(opts.bits, OPTS_DEFAULT_BITS);
    CU_ASSERT_STRING_EQUAL(opts.lang, OPTS_DEFAULT_LANG);

    TEST_BITS(128);
    TEST_BITS(160);
    TEST_BITS(192);
    TEST_BITS(224);
    TEST_BITS(256);

    TEST_LANG("cs");
    TEST_LANG("en");
    TEST_LANG("es");
    TEST_LANG("fr");
    TEST_LANG("it");
    TEST_LANG("pt");
    TEST_LANG("ja");
    TEST_LANG("ko");
    TEST_LANG("zh_cn");
    TEST_LANG("zh_tw");
}
