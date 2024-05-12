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

#ifndef BIPS39_WORDLIST_H
#define BIPS39_WORDLIST_H

/** @brief Wordlist structure */
typedef struct {
    const char *const lang;  /**< Language of the wordlist */
    const char *const words; /**< List of words in the wordlist */
} wordlist_t;

/** @brief Wordlists (defined in wordlists.c) */
extern const wordlist_t wordlists[];

/**

    @brief Build the wordlist index for a given language.

    This function returns the wordlist index for a given language. The index is
    an array of pointers to the words in the wordlist.

    @param lang   The language of the wordlist.
    @param index  An array of pointers to the words in the wordlist.

    @return 1 if the language is found, 0 otherwise.

*/
int wordlist_get_index(const char *lang, const char *index[2048]);

#endif /* BIPS39_WORDLIST_H */
