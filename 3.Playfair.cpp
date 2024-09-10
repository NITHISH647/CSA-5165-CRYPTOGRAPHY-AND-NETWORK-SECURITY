#include <stdio.h>
#include <string.h>

int main() {
    char keyword[100], plaintext[100];
    char matrix[5][5];
    int i, j, k = 0, used[26] = {0};
    int x1, y1, x2, y2;
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    for (i = 0; i < strlen(keyword); i++) {
        if (keyword[i] == 'j') {
            keyword[i] = 'i';  
        }
        if (!used[keyword[i] - 'a']) { 
            matrix[k / 5][k % 5] = keyword[i];
            used[keyword[i] - 'a'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (i + 'a' != 'j' && !used[i]) {
            matrix[k / 5][k % 5] = i + 'a';
            k++;
        }
    }
    printf("\n5x5 Playfair matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nEncrypted text: ");
    for (i = 0; plaintext[i] != '\0'; i += 2) {
        if (plaintext[i] == 'j') plaintext[i] = 'i'; 
        if (plaintext[i + 1] == 'j') plaintext[i + 1] = 'i';
        if (plaintext[i + 1] == '\0' || plaintext[i] == plaintext[i + 1]) {
            plaintext[i + 1] = 'x';
        }
        for (x1 = 0; x1 < 5; x1++) {
            for (y1 = 0; y1 < 5; y1++) {
                if (matrix[x1][y1] == plaintext[i]) break;
            }
            if (y1 < 5) break;
        }
        for (x2 = 0; x2 < 5; x2++) {
            for (y2 = 0; y2 < 5; y2++) {
                if (matrix[x2][y2] == plaintext[i + 1]) break;
            }
            if (y2 < 5) break;
        }
        if (x1 == x2) {
            printf("%c%c", matrix[x1][(y1 + 1) % 5], matrix[x2][(y2 + 1) % 5]);
        } else if (y1 == y2) { 
            printf("%c%c", matrix[(x1 + 1) % 5][y1], matrix[(x2 + 1) % 5][y2]);
        } else { 
            printf("%c%c", matrix[x1][y2], matrix[x2][y1]);
        }
    }
    printf("\n");

    return 0;
}
