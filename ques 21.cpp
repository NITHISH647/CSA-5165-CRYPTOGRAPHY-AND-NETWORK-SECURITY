#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(char *block1, char *block2, char *output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void encrypt_block(char *plaintext, char *key, char *ciphertext) {
    xor_blocks(plaintext, key, ciphertext, BLOCK_SIZE);
}

void decrypt_block(char *ciphertext, char *key, char *plaintext) {
    xor_blocks(ciphertext, key, plaintext, BLOCK_SIZE);
}

void apply_padding(char *data, int *data_len) {
    int padding_len = BLOCK_SIZE - (*data_len % BLOCK_SIZE);
    if (padding_len == 0) padding_len = BLOCK_SIZE;
    data[*data_len] = 0x80;
    for (int i = 1; i < padding_len; i++) {
        data[*data_len + i] = 0x00;
    }
    *data_len += padding_len;
}

void ecb_encrypt(char *plaintext, int plaintext_len, char *key, char *ciphertext) {
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        encrypt_block(plaintext + i, key, ciphertext + i);
    }
}

void cbc_encrypt(char *plaintext, int plaintext_len, char *key, char *iv, char *ciphertext) {
    char temp[BLOCK_SIZE];
    xor_blocks(plaintext, iv, temp, BLOCK_SIZE);
    encrypt_block(temp, key, ciphertext);
    for (int i = BLOCK_SIZE; i < plaintext_len; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, ciphertext + i - BLOCK_SIZE, temp, BLOCK_SIZE);
        encrypt_block(temp, key, ciphertext + i);
    }
}

void cfb_encrypt(char *plaintext, int plaintext_len, char *key, char *iv, char *ciphertext) {
    char temp[BLOCK_SIZE];
    encrypt_block(iv, key, temp);
    xor_blocks(plaintext, temp, ciphertext, BLOCK_SIZE);
    for (int i = BLOCK_SIZE; i < plaintext_len; i += BLOCK_SIZE) {
        encrypt_block(ciphertext + i - BLOCK_SIZE, key, temp);
        xor_blocks(plaintext + i, temp, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    char key[BLOCK_SIZE] = { 'k', 'e', 'y', 's', 'e', 'c', 'r', 't' };
    char iv[BLOCK_SIZE] = { 'i', 'n', 'i', 't', 'v', 'e', 'c', 't' };
    char plaintext[64] = "thisisatestplaintext";
    int plaintext_len = strlen(plaintext);

    apply_padding(plaintext, &plaintext_len);

    char ciphertext_ecb[64];
    ecb_encrypt(plaintext, plaintext_len, key, ciphertext_ecb);

    char ciphertext_cbc[64];
    cbc_encrypt(plaintext, plaintext_len, key, iv, ciphertext_cbc);

    char ciphertext_cfb[64];
    cfb_encrypt(plaintext, plaintext_len, key, iv, ciphertext_cfb);

    return 0;
}
