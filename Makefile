all: bip39 bip39.1

clean:
	-rm -f bip39

WORDLIST_HEADERS := \
	wordlist.cs.h \
	wordlist.en.h \
	wordlist.es.h \
	wordlist.fr.h \
	wordlist.it.h \
	wordlist.ja.h \
	wordlist.ko.h \
	wordlist.pt.h \
	wordlist.zh_cn.h \
	wordlist.zh_tw.h \

LIBS := -lsodium

bip39: bip39.c $(WORDLIST_HEADERS)
	gcc -s -Os -fwhole-program -Wall -Wextra -Werror -std=c99 -lsodium -o bip39 bip39.c

bip39.1: bip39.1.ronn index.txt
	ronn --pipe -r $< >$@

install: bip39 bip39.1 LICENSE README.md
	cat bip39.1 | gzip > bip39.1.gz
	install -o0 -g0 -Dm755 bip39 /usr/bin/
	install -o0 -g0 -Dm644 bip39.1.gz /usr/share/man/man1/
	install -o0 -g0 -Dm644 LICENSE /usr/share/doc/bip39/
	install -o0 -g0 -Dm644 README.md /usr/share/doc/bip39/
