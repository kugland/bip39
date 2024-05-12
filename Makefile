all:
	meson setup build
	ninja -C build

test: build
	./build/bip39_tests

clean:
	rm -rf build

format:
	clang-format -i src/*.[ch] tests/*.[ch]

mkwordlists:
	./mkwordlists.pl
