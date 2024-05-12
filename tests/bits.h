#include "../src/bits.h"

#include <stdlib.h>
#include <endian.h>
#include <unistd.h>
#include <CUnit/Basic.h>

void
test__bits(void)
{
    {
        uint64_t bits = 0x5555555555555555;
        for (int i = 0; i < 63; i++)
            CU_ASSERT_EQUAL(bits_get(i, 1, (uint8_t *)&bits), i & 1);

        bits = 0xaaaaaaaaaaaaaaaa;
        for (int i = 0; i < 63; i++)
            CU_ASSERT_EQUAL(bits_get(i, 1, (uint8_t *)&bits), !(i & 1));
    }

    {
        uint64_t bits = 0;
        uint64_t expect = 0;
        for (int i = 0; i < 64; i++) {
            bits_set(i, 1, (uint8_t *)&bits, 1);
            expect >>= 1;
            expect |= INT64_MIN;
            CU_ASSERT_EQUAL(bits, htobe64(expect));
        }
        for (int i = 0; i < 64; i++) {
            bits_set(i, 1, (uint8_t *)&bits, 0);
            expect >>= 1;
            CU_ASSERT_EQUAL(bits, htobe64(expect));
        }
    }

    {
        for (int i = 0; i < 128; i++) {
            for (int start = 0; start < 64; start++) {
                for (int count = 0; count < (63 - start); count++) {
                    uint64_t value;
                    uint64_t bits = 0;
                    if (getentropy(&value, sizeof(value)) != 0)
                        abort();
                    value = -1;
                    bits_set(start, count, (uint8_t *)&bits, value);
                    uint64_t expect = bits_get(start, count, (uint8_t *)&bits);
                    CU_ASSERT_EQUAL(value & ((1ULL << (count)) - 1), expect);
                }
            }
        }
    }
}
