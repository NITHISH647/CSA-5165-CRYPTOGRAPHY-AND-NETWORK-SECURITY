#include <stdio.h>
#include <string.h>

int main() {
    char keyword[] = "playfair";
    char ciphertext[100];
	printf("enter cipher text");
	scanf("%s",ciphertext);
    char matrix[5][5];
    char alphabet[26];
    char plaintext[100];
    int i, j, k = 0;
    int used[26] = {0};
    int row1, col1, row2, col2;
    for (i = 0; i < 26; i++) {
        alphabet[i] = 'a' + i;
    }
    for (i = 0; keyword[i] != '\0'; i++) {
        if (keyword[i] != 'j' && !used[keyword[i] - 'a']) {
            matrix[k / 5][k % 5] = keyword[i];
            used[keyword[i] - 'a'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i] && i != 'j' - 'a') {
            matrix[k / 5][k % 5] = 'a' + i;
            k++;
        }
    }
    for (i = 0; ciphertext[i] != '\0'; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        if (a == ' ' || b == ' ') {
            i--;
            continue;
        }
        for (row1 = 0; row1 < 5; row1++) {

            for (col1 = 0; col1 < 5; col1++) {
                if (matrix[row1][col1] == a) {
                    break;
                }
            }
            if (col1 < 5) break;
        }
        for (row2 = 0; row2 < 5; row2++) {
            for (col2 = 0; col2 < 5; col2++) {
                if (matrix[row2][col2] == b) {
                    break;
                }
            }
            if (col2 < 5) break;
        }
        if (row1 == row2) {
            plaintext[i / 2 * 2] = matrix[row1][(col1 + 4) % 5];
            plaintext[i / 2 * 2 + 1] = matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            plaintext[i / 2 * 2] = matrix[(row1 + 4) % 5][col1];
            plaintext[i / 2 * 2 + 1] = matrix[(row2 + 4) % 5][col2];
        } else {
            plaintext[i / 2 * 2] = matrix[row1][col2];
            plaintext[i / 2 * 2 + 1] = matrix[row2][col1];
        }
    }
    plaintext[strlen(ciphertext) / 2] = '\0';
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}
