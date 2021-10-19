# bip39(1)
**Generate mnemonic codes according to BIP-0039.**

![AUR version](https://img.shields.io/aur/version/bip39-git)

### SYNOPSIS

  **`bip39`** **<var>`BITS`</var>** **`[`<var>`LANGUAGE`</var>`]`**

### DESCRIPTION

**bip39** generates a mnemonic code according to BIP-0039 (“Mnemonic code
for generating deterministic keys”, M. Palatinus, P. Rusnak, A. Voisine,
and S. Bowe).[^BIP0039]

This algorithm is _not_ recommended for new wallets. It was implemented
here to generate mnemonic passwords for other uses.

#### OPTIONS

  * <var>BITS</var>:
    Number of bits in the mnemonic code. (_required_)
    
    Valid values are **128**, **160**, **192**, **224**, and **256**.

  * <var>LANG</var>:
    Language of the mnemonic code. (_optional_)
    
    Valid values are **en** (English), **es** (Spanish), **fr** (French),
    **it** (Italian), **ja** (Japanese), **ko** (Korean), **pt**
    (Portuguese), **zh_cn** (Chinese simplified), and **zh_tw** (Chinese
    traditional).

### COPYRIGHT & LICENSE

This software was written by André Kugland and is licensed under the MIT license.

### SEE ALSO

[pwgen(1)](https://linux.die.net/man/1/pwgen)

[^BIP0039]: For a description of the algorithm, see https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki.
