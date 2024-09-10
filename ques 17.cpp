#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 64
#define KEY_SIZE 48

int main() {
    int keys[16] = {
        0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 
        0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10
    };
    int reverse_keys[16];
    for (int i = 0; i < 16; i++) {
        reverse_keys[i] = keys[15 - i]; 
    }
    char text[BLOCK_SIZE + 1] = "exampletext";
    for (int round = 0; round < 16; round++) {
        int current_key = reverse_keys[round]; 
        printf("Round %d: Using key %X\n", round + 1, current_key);
        
        for (int i = 0; i < strlen(text); i++) {
            text[i] = text[i] ^ current_key; 
        }
    }
    
    printf("Decrypted text: %s\n", text);
    return 0;
}
