#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10
#define MAX_CIPHERTEXT_LEN 100

int main() {
    char ciphertext[MAX_CIPHERTEXT_LEN];
    int num_plaintexts = 10;
    int frequency[ALPHABET_SIZE] = {0};
    int possible_shifts[ALPHABET_SIZE];
    char plaintext[MAX_CIPHERTEXT_LEN + 1];
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            frequency[ciphertext[i] - 'a']++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        possible_shifts[i] = i;
    }
    printf("Top %d possible plaintexts:\n", num_plaintexts);
    for (int i = 0; i < num_plaintexts; i++) {
        for (int j = 0; j < length; j++) {
            if (ciphertext[j] >= 'a' && ciphertext[j] <= 'z') {
                plaintext[j] = ((ciphertext[j] - 'a' - possible_shifts[i] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            } else {
                plaintext[j] = ciphertext[j];
            }
        }
        plaintext[length] = '\0';
        printf("%d: %s\n", i + 1, plaintext);
    }
    return 0;
}
