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

#ifndef BIPS39_PRINT_H
#define BIPS39_PRINT_H

#include <stdbool.h>

/**

    @brief Print a mnemonic phrase to stdout

    @param lang     The language of the mnemonic phrase
    @param numbered Whether to number the words in the mnemonic phrase
    @param phrase   Pointers to the words of the mnemonic phrase

    @return 0 on success, -1 on error

*/
int print_phrase(const char *lang, bool numbered, const char **phrase);

#endif /* BIPS39_PRINT_H */
