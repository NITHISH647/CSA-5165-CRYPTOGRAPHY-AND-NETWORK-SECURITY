#include <stdio.h>
#include <string.h>
int main() {
    char plaintext[100], key[100];
    int i, j = 0, key_len;
    printf("Enter the plaintext : ");
    scanf("%s", plaintext);
    printf("Enter the key : ");
    scanf("%s", key);
    key_len = strlen(key);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = (plaintext[i] - 'a' + (key[j % key_len] - 'a')) % 26 + 'a';
            j++;
        }
    }
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
