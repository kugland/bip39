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
#include "opts.h"
#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sodium.h>

#ifdef CUNIT_TESTING /* main() shouldn't be compiled if testing with CUnit */
__attribute__((weak))
#endif

int
main(int argc, char *argv[])
{
    if (sodium_init() == -1)
        return 1;

    opts_t opts;
    const char **phrase = NULL;

    opts_from_cmdline(argc, argv, &opts);

    if ((phrase = bip39_phrase(opts.bits, opts.lang, NULL)) == NULL)
        goto failure;
    if (print_phrase(opts.lang, opts.numbered, phrase) != 0)
        goto failure;

    sodium_free(phrase);
    return EXIT_SUCCESS;

failure:
    sodium_free(phrase);
    perror("bip39");
    return EXIT_FAILURE;
}
