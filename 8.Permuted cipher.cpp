#include <stdio.h>
#include <string.h>

int main() {
    char plaintext[100], keyword[100], ciphertext[26];
    char alphabet[26];
    int i, j, k = 0, used[26] = {0};
    for (i = 0; i < 26; i++) {
        alphabet[i] = 'a' + i;
    }
    printf("Enter plaintext (lowercase only): ");
    scanf("%s", plaintext);
    printf("Enter keyword (lowercase only): ");
    scanf("%s", keyword);
    for (i = 0; keyword[i] != '\0'; i++) {
        if (!used[keyword[i] - 'a']) { 
            ciphertext[k++] = keyword[i];
            used[keyword[i] - 'a'] = 1;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            ciphertext[k++] = alphabet[i];
        }
    }
    printf("Generated Cipher Alphabet: ");
    for (i = 0; i < 26; i++) {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = ciphertext[plaintext[i] - 'a'];
        }
    }
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
