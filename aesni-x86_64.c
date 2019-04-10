#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "aesni-x86_64.h"

typedef unsigned char byte;

int main(int argc, char* argv[])
{
    /* Test key from FIPS 197 */
    const byte kb[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    const byte pb[] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
    };

    const byte cb[] = {
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
        0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97
    };

    /* Scratch */
    byte buf[16];
    int result;

    /********************************************/

    AES_KEY ekey;
    result = aesni_set_encrypt_key(kb, sizeof(kb)*8, & ekey);
    assert(result == 0);

    aesni_encrypt(pb, buf, &ekey);
    if (memcmp(cb, buf, 16) == 0) {
        printf("Encrypted plaintext!\n");
    }
    else
        printf("Failed to encrypt plaintext!\n");

    /********************************************/

    AES_KEY dkey;
    result = aesni_set_decrypt_key(kb, sizeof(kb)*8, & dkey);
    assert(result == 0);

    aesni_decrypt(cb, buf, &dkey);
    if (memcmp(pb, buf, 16) == 0)
        printf("Decrypted ciphertext!\n");
    else
        printf("Failed to decrypt ciphertext!\n");

    return 0;
}
