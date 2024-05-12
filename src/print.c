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

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

static const char nums[24][5]
    = { " 1. ", " 2. ", " 3. ", " 4. ", " 5. ", " 6. ", " 7. ", " 8. ",
        " 9. ", "10. ", "11. ", "12. ", "13. ", "14. ", "15. ", "16. ",
        "17. ", "18. ", "19. ", "20. ", "21. ", "22. ", "23. ", "24. " };

static const char nums_cjk[24][10]
    = { "　１　", "　２　", "　３　", "　４　", "　５　", "　６　",
        "　７　", "　８　", "　９　", "１０　", "１１　", "１２　",
        "１３　", "１４　", "１５　", "１６　", "１７　", "１８　",
        "１９　", "２０　", "２１　", "２２　", "２３　", "２４　" };

int
print_mnemonic(const char *lang, bool numbered, const char **mnemonic)
{
    errno = 0;

    bool cjk = strcmp(lang, "ja") == 0 || strcmp(lang, "ko") == 0
            || strcmp(lang, "zh_cn") == 0 || strcmp(lang, "zh_tw") == 0;

    for (int i = 0; mnemonic[i]; i++) {
        if (i > 0) {
            /* Add a space between words */
            const char *pre = numbered ? "\n" : (cjk ? "　" : " ");
            if (write(STDOUT_FILENO, pre, strlen(pre)) == -1)
                return -1;
        }
        if (numbered) {
            /* Print the word number */
            const char *num = !cjk ? nums[i] : nums_cjk[i];
            if (write(STDOUT_FILENO, num, strlen(num)) == -1)
                return -1;
        }
        /* Print the word */
        if (write(STDOUT_FILENO, mnemonic[i], strlen(mnemonic[i])) == -1)
            return 1;
        mnemonic[i] = NULL; /* Zero out the mnemonic */
    }
    if (write(STDOUT_FILENO, "\n", 1) == -1) /* Final newline */
        return -1;

    return 0;
}
