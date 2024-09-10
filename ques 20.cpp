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

int main() {
    char key[BLOCK_SIZE] = { 'k', 'e', 'y', 's', 'e', 'c', 'r', 't' }; 

    char iv[BLOCK_SIZE] = { 'i', 'n', 'i', 't', 'v', 'e', 'c', 't' };
    char plaintext1[BLOCK_SIZE] = { 'b', 'l', 'o', 'c', 'k', 'o', 'n', 'e' };
    char plaintext2[BLOCK_SIZE] = { 'b', 'l', 'o', 'c', 'k', 't', 'w', 'o' }; 

    char ciphertext_ecb1[BLOCK_SIZE], ciphertext_ecb2[BLOCK_SIZE];
    encrypt_block(plaintext1, key, ciphertext_ecb1);
    encrypt_block(plaintext2, key, ciphertext_ecb2); 
    char ciphertext_cbc1[BLOCK_SIZE], ciphertext_cbc2[BLOCK_SIZE];
    char temp[BLOCK_SIZE];

    xor_blocks(plaintext1, iv, temp, BLOCK_SIZE); 
    encrypt_block(temp, key, ciphertext_cbc1);  
    xor_blocks(plaintext2, ciphertext_cbc1, temp, BLOCK_SIZE);
    encrypt_block(temp, key, ciphertext_cbc2);                
    ciphertext_cbc1[0] ^= 0xFF; 
    char decrypted_cbc1[BLOCK_SIZE], decrypted_cbc2[BLOCK_SIZE];
    decrypt_block(ciphertext_cbc1, key, temp);  
    xor_blocks(temp, iv, decrypted_cbc1, BLOCK_SIZE); 
    decrypt_block(ciphertext_cbc2, key, temp);  
    xor_blocks(temp, ciphertext_cbc1, decrypted_cbc2, BLOCK_SIZE); 
    printf("Original Plaintext 1: %s\n", plaintext1);
    printf("Original Plaintext 2: %s\n", plaintext2);

    printf("\nECB Mode Encryption:\n");
    printf("Ciphertext Block 1 (ECB): ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", (unsigned char)ciphertext_ecb1[i]);
    printf("\nCiphertext Block 2 (ECB): ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", (unsigned char)ciphertext_ecb2[i]);
    printf("\n");

    printf("\nCBC Mode Encryption (with error in block 1):\n");
    printf("Ciphertext Block 1 (CBC): ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", (unsigned char)ciphertext_cbc1[i]);
    printf("\nCiphertext Block 2 (CBC): ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", (unsigned char)ciphertext_cbc2[i]);
    printf("\n");

    printf("\nCBC Mode Decryption (with error in block 1):\n");
    printf("Decrypted Block 1 (CBC): %s\n", decrypted_cbc1);
    printf("Decrypted Block 2 (CBC): %s\n", decrypted_cbc2);

    return 0;
}
