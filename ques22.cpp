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
void sdesDecrypt(unsigned char ciphertext[8], unsigned char key[10], unsigned char plaintext[8]) {
    for (int i = 0; i < 8; i++) {
        plaintext[i] = ciphertext[i] ^ key[i % 10];  
    }
}
void cbcEncrypt(unsigned char plaintext[16], unsigned char key[10], unsigned char iv[8], unsigned char ciphertext[16]) {
    unsigned char previousBlock[8], currentBlock[8];
    memcpy(previousBlock, iv, 8); 
    for (int i = 0; i < 16; i += 8) {
        xorBlocks(&plaintext[i], previousBlock, currentBlock, 8); 
        sdesEncrypt(currentBlock, key, &ciphertext[i]);      
        memcpy(previousBlock, &ciphertext[i], 8);          
    }
}
void cbcDecrypt(unsigned char ciphertext[16], unsigned char key[10], unsigned char iv[8], unsigned char decryptedtext[16]) {
    unsigned char previousBlock[8], decryptedBlock[8];
    memcpy(previousBlock, iv, 8); 
    for (int i = 0; i < 16; i += 8) {
        sdesDecrypt(&ciphertext[i], key, decryptedBlock);   
        xorBlocks(decryptedBlock, previousBlock, &decryptedtext[i], 8); 
        memcpy(previousBlock, &ciphertext[i], 8);           
    }
}
void printBinary(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}
int main() {
    unsigned char plaintext[16] = {0x00, 0x01, 0x02, 0x03};  
    unsigned char key[10] = {0x0F, 0xFD};                
    unsigned char iv[8] = {0xAA};                    
    unsigned char ciphertext[16], decryptedtext[16];
    printf("Original plaintext: ");
    printBinary(plaintext, 4);
    cbcEncrypt(plaintext, key, iv, ciphertext);
    printf("Ciphertext: ");
    printBinary(ciphertext, 4);
    cbcDecrypt(ciphertext, key, iv, decryptedtext);
    printf("Decrypted plaintext: ");
    printBinary(decryptedtext, 4);
    return 0;
}