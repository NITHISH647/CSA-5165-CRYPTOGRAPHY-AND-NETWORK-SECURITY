#include <stdio.h>
#include <string.h>
void xorBlocks(unsigned char *a, unsigned char *b, unsigned char *result, int length) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void sdesEncrypt(unsigned char plaintext[8], unsigned char key[10], unsigned char ciphertext[8]) {
    for (int i = 0; i < 8; i++) {
        ciphertext[i] = plaintext[i] ^ key[i % 10]; 
    }
}
void ctrEncryptDecrypt(unsigned char plaintext[24], unsigned char key[10], unsigned char counter[8], unsigned char ciphertext[24], int textLength) {
    unsigned char encryptedCounter[8], keyStream[8], currentCounter[8];
    memcpy(currentCounter, counter, 8); 
    for (int i = 0; i < textLength; i += 8) {
        sdesEncrypt(currentCounter, key, encryptedCounter);
        xorBlocks(&plaintext[i], encryptedCounter, &ciphertext[i], 8);
        for (int j = 7; j >= 0; j--) {
            if (++currentCounter[j] != 0) break;
        }
    }
}
void printBinary(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
int main() {
    unsigned char plaintext[24] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x04}; 
    unsigned char key[10] = {0x0F, 0xFD};  
    unsigned char counter[8] = {0x00};                     
    unsigned char ciphertext[24], decryptedtext[24];
    printf("Original plaintext: ");
    printBinary(plaintext, 6);
    ctrEncryptDecrypt(plaintext, key, counter, ciphertext, 6);
    printf("Ciphertext: ");
    printBinary(ciphertext, 6);
    memset(counter, 0x00, 8); 
    ctrEncryptDecrypt(ciphertext, key, counter, decryptedtext, 6);
    printf("Decrypted plaintext: ");
    printBinary(decryptedtext, 6);
    return 0;
}