#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 
void xor_blocks(char *block1, char *block2, char *output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

int main() {
    char key1[BLOCK_SIZE] = { 'k', 'e', 'y', '1', 'k', 'e', 'y', '1' }; 
    char key2[BLOCK_SIZE] = { 'k', 'e', 'y', '2', 'k', 'e', 'y', '2' }; 
    char key3[BLOCK_SIZE] = { 'k', 'e', 'y', '3', 'k', 'e', 'y', '3' };
    char iv[BLOCK_SIZE] = { 'i', 'n', 'i', 't', 'v', 'e', 'c', 't' }; 
    char plaintext[BLOCK_SIZE] = "example"; 
    char ciphertext[BLOCK_SIZE];
    xor_blocks(plaintext, iv, ciphertext, BLOCK_SIZE);
    xor_blocks(ciphertext, key1, ciphertext, BLOCK_SIZE);  
    xor_blocks(ciphertext, key2, ciphertext, BLOCK_SIZE);  
    xor_blocks(ciphertext, key3, ciphertext, BLOCK_SIZE);  
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    return 0;
}
