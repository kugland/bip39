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

#include "opts.h"
#include "wordlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *help_message
    = "bip39 - A command-line tool to generate BIP-0039 mnemonic phrases.\n"
      "\n"
      "USAGE\n"
      "    bip39 [OPTIONS]\n"
      "\n"
      "OPTIONS\n"
      "    -b BITS   Number of entropy bits.  Default: 128.\n"
      "              Valid values are 128, 160, 192, 224, and 256.\n"
      "\n"
      "    -l LANG   Language of the word list.  Default: 'en'.\n"
      "              Valid values are 'cs' (Czech), 'en' (English),\n"
      "              'es' (Spanish), 'fr' (French), 'it' (Italian),\n"
      "              'ja' (Japanese), 'ko' (Korean), 'pt' (Portuguese),\n"
      "              'zh_cn' (Simplified Chinese), and 'zh_tw'\n"
      "              (Traditional Chinese).\n"
      "\n"
      "    -n        Add a number to each word in the mnemonic phrase.\n"
      "\n"
      "    -h        Show help message and exit.\n"
      "\n"
      "    -V        Show version information and exit.\n"
      "\n"
      "COPYRIGHT & LICENSE\n"
      "    Copyright (c) 2021-2024 Andre Kugland.  Released under the\n"
      "    MIT License -- see the accompanying LICENSE file for more\n"
      "    information.\n";

static const char valid_bits[6][4] = { "128", "160", "192", "224", "256", "" };

void
opts_from_cmdline(int argc, char *argv[], opts_t *opts)
{
    int opt, i;

    opts->bits = OPTS_DEFAULT_BITS;
    opts->lang = OPTS_DEFAULT_LANG;
    opts->numbered = OPTS_DEFAULT_NUMBERED;

    while ((opt = getopt(argc, argv, "b:l:nhV")) != -1) {
        switch (opt) {
        case 'b':
            for (i = 0; valid_bits[i][0] != '\0'; i++)
                if (strcmp(optarg, valid_bits[i]) == 0)
                    break;
            if (valid_bits[i][0] == '\0')
                goto invalid;
            opts->bits = atoi(optarg);
            break;
        case 'l':
            opts->lang = optarg;
            for (i = 0; wordlists[i].lang != NULL; i++)
                if (strcmp(wordlists[i].lang, opts->lang) == 0)
                    break;
            if (wordlists[i].lang == NULL)
                goto invalid;
            break;
        case 'n':
            opts->numbered = true;
            break;
        case 'h':
            fprintf(stderr, "%s", help_message);
            exit(EXIT_SUCCESS);
        case 'V':
            printf("bip39 v" PROJECT_VERSION "\n");
            exit(EXIT_SUCCESS);
        default:
            goto usage;
        }
    }
    if (optind < argc) {
        fprintf(stderr, "%s: unexpected argument -- '%s'.\n", "bip39",
                argv[optind]);
        goto usage;
    }
    optind = 1;
    return;

invalid:
    fprintf(stderr, "%s: invalid argument for option '%c' -- '%s'.\n",
            "bip39", opt, optarg);

usage:
    fprintf(stderr, "Try '%s -h' for more information.\n", "bip39");
    exit(EXIT_FAILURE);
}
