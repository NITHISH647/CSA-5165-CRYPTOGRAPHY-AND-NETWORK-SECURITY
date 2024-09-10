#include <stdio.h>

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
int main() {
    char ciphertext[100];
    int a, b, a_inverse, i;
    printf("Enter the ciphertext (lowercase only): ");
    scanf("%s", ciphertext);
    a = 7; 
    b = 23; 
    a_inverse = mod_inverse(a, 26);
    
    if (a_inverse == -1) {
        printf("No modular inverse found for a\n");
        return 0;
    }
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = ((a_inverse * ((ciphertext[i] - 'a' - b + 26) % 26)) % 26) + 'a';
        }
    }
    printf("Decrypted text: %s\n", ciphertext);
    return 0;
}
