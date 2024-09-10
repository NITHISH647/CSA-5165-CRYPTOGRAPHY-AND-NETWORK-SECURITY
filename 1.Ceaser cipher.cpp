#include <stdio.h>

int main() {
    char text[100];
    int i, k;
    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter the value of k (1-25): ");
    scanf("%d", &k);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + k) % 26 + 'a';
        }
    }
    printf("Encrypted text: %s\n", text);

    return 0;
}
