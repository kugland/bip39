# bip39

A command-line tool to generate BIP0039[^BIP0039] mnemonic phrases.

[^BIP0039]: BIP0039 is a proposed standard for generating mnemonic phrases from
a random number to create deterministic keys for wallets. *The standard was
never approved though, so its use is **not** recommended for new wallets*, even
though many wallets still support it. [BIP0039: “Mnemonic code for generating
deterministic keys”, M. Palatinus, P. Rusnak, A. Voisine, and S. Bowe](
https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki).

## Building and installing

```bash
meson setup build
ninja -C build
ninja -C build install
```

## Usage

`bip39 [OPTIONS]`

### Options

  * **-b** <var>BITS</var>:
    Number of bits in the mnemonic code.

    Valid values are **128**, **160**, **192**, **224**, and **256**.

  * **-l** <var>LANG</var>:
    Language of the mnemonic words.

    Valid values are **cs** (Czech), **en** (English), **es** (Spanish), **fr**
    (French), **it** (Italian), **ja** (Japanese), **ko** (Korean), **pt**
    (Portuguese), **zh_cn** (Simplified Chinese), and **zh_tw** (Traditional
    Chinese).

  * **-n**:
    Add a number to each word in the mnemonic phrase.

  * **-h**:
    Show help message and exit.

  * **-V**:
    Show version information and exit.

## Copyright & License

This project was written by André Kugland, and is released under the MIT
License — see the [LICENSE](LICENSE) file for details.
