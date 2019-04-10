#ifndef CRYPTOGAMS_AESNI_X86_64_H
#define CRYPTOGAMS_AESNI_X86_64_H

#define AES_MAXNR 14

struct aes_key_st {
    unsigned int rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;

int aesni_set_encrypt_key(const unsigned char *userKey, int bits, AES_KEY *key);
int aesni_set_decrypt_key(const unsigned char *userKey, int bits, AES_KEY *key);

void aesni_encrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key);
void aesni_decrypt(const unsigned char *in, unsigned char *out, const AES_KEY *key);

#endif
