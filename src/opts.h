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

#ifndef BIPS39_OPTS_H
#define BIPS39_OPTS_H

#include <stdbool.h>

#define OPTS_DEFAULT_BITS 128
#define OPTS_DEFAULT_LANG "en"
#define OPTS_DEFAULT_NUMBERED false

/** @brief Command line options. */
typedef struct {
    int bits;      /**< Number of bits in the mnemonic seed. */
    char *lang;    /**< Language of the wordlist to use. */
    bool numbered; /**< Whether the words are numbered */
} opts_t;

/**

    @brief Parse command line options.

    This function parses the command line options and sets the corresponding
    fields in the opts_t structure.

    Options not given on the command line are set to their default values.

    When the options ‘-h’ or ‘-V’ are given, this function will print the
    corresponding message and exit. Also, when an invalid option is given, this
    function will print an error message and exit.

    @param argc  The number of command line arguments.
    @param argv  An array of command line argument strings.
    @param opts  A pointer to the opts_t structure to be filled in.

*/
void opts_from_cmdline(int argc, char *argv[], opts_t *opts);

#endif /* BIPS39_OPTS_H */
