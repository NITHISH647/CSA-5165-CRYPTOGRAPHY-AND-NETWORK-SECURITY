#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    char plaintext[100];
    int a, b, i, valid_a;
    printf("Enter plaintext (lowercase only): ");
    scanf("%s", plaintext);
    do {
        printf("Enter value of a (must be coprime with 26): ");
        scanf("%d", &a);
        valid_a = (gcd(a, 26) == 1); 
        if (!valid_a) {
            printf("Invalid value of a. It must be coprime with 26.\n");
        }
    } while (!valid_a);

    printf("Enter value of b: ");
    scanf("%d", &b);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        }
    }
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
