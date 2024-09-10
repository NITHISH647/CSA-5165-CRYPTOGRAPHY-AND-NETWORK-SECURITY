#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define ALPHABET_SIZE 26

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key) / sizeof(key[0]);
    char ciphertext[MAX_LEN];
    char decrypted_text[MAX_LEN];

    int text_len = strlen(plaintext);

    for (int i = 0; i < text_len; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[i % key_len];
            ciphertext[i] = ((plaintext[i] - 'a' + shift) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[text_len] = '\0';
    printf("Ciphertext: %s\n", ciphertext);

    for (int i = 0; i < text_len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = key[i % key_len];
            decrypted_text[i] = ((ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            decrypted_text[i] = ciphertext[i];
        }
    }
    decrypted_text[text_len] = '\0';
    printf("Decrypted text: %s\n", decrypted_text);

    char target_plaintext[] = "cash not needed";
    int target_key[MAX_LEN];
    int target_key_len = strlen(ciphertext);

    for (int i = 0; i < target_key_len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            target_key[i] = (ciphertext[i] - target_plaintext[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            target_key[i] = 0;
        }
    }

    printf("Target key stream: ");
    for (int i = 0; i < target_key_len; i++) {
        printf("%d ", target_key[i]);
    }
    printf("\n");

    for (int i = 0; i < text_len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = target_key[i % target_key_len];
            decrypted_text[i] = ((ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            decrypted_text[i] = ciphertext[i];
        }
    }
    decrypted_text[text_len] = '\0';
    printf("Decrypted text with target key: %s\n", decrypted_text);

    return 0;
}
