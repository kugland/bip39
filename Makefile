all: bip39 bip39.1

ifndef PREFIX
PREFIX = /usr/local
endif

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
	gcc $(CFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror -std=c99 $(LIBS) -o bip39 bip39.c

bip39.1: bip39.1.ronn index.txt
	ronn --pipe -r $< >$@

install: bip39 bip39.1 LICENSE README.md
	cat bip39.1 | gzip > bip39.1.gz
	mkdir "$(PREFIX)/share/doc/bip39"
	install -o0 -g0 -Dm755 bip39 "$(PREFIX)/bin/"
	install -o0 -g0 -Dm644 bip39.1.gz "$(PREFIX)/share/man/man1/"
	install -o0 -g0 -Dm644 LICENSE "$(PREFIX)/share/doc/bip39/"
	install -o0 -g0 -Dm644 README.md "$(PREFIX)/share/doc/bip39/"
