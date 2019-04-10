# AES-NI library from OpenSSL

Custom usage of OpenSSL AES-NI library.

## Prerequisites
Linux x86_64 OS is required. Tested on a 2nd generation Intel i5 CPU.

Remove all instances of *OPENSSL_ia32cap_P* from *aesni-x86_64.pl*

## Usage
```
cd openssl-aesni

chmod +x *.pl

./aesni-x86_64.pl aesni-x86_64.s

gcc -march=sandybridge -c aesni-x86_64.s

gcc aesni-x86_64.c aesni-x86_64.o -o aesni-x86_64.exe

gcc -O3 -D_XOPEN_SOURCE=700 aesni-x86_64-test.c aesni-x86_64.o -o aesni-x86_64-test.exe
```

## References
[OpenSSL](https://github.com/openssl/openssl) - AES-NI library

[Cryptograms AES](https://wiki.openssl.org/index.php/Cryptogams_AES) - example test program and benchmark