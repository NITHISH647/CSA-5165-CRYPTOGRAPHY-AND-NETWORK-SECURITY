#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
int main() {
    char matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'K', 'U', 'N', 'O', 'P'},
        {'Q', 'Z', 'V', 'W', 'X'},
        {'Y', 'E', 'L', 'A', 'R'},
        {'G', 'D', 'S', 'T', 'B'}
    };

    char plaintext[100], prepared_text[100], encrypted_text[100];
    int i, j, row1, col1, row2, col2;

    printf("Enter message: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    int k = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            prepared_text[k++] = toupper(plaintext[i]);
        }
    }
    prepared_text[k] = '\0';

    int len = strlen(prepared_text);
    if (len % 2 != 0) {
        prepared_text[len++] = 'X';
        prepared_text[len] = '\0';
    }

    for (i = 0, j = 0; i < len; i += 2) {
        char a = prepared_text[i];
        char b = prepared_text[i + 1];
        
        for (row1 = 0; row1 < SIZE; row1++) {
            for (col1 = 0; col1 < SIZE; col1++) {
                if (matrix[row1][col1] == a) break;
            }
            if (col1 < SIZE) break;
        }
        
        for (row2 = 0; row2 < SIZE; row2++) {
            for (col2 = 0; col2 < SIZE; col2++) {
                if (matrix[row2][col2] == b) break;
            }
            if (col2 < SIZE) break;
        }

        if (row1 == row2) {
            encrypted_text[j++] = matrix[row1][(col1 + 1) % SIZE];
            encrypted_text[j++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted_text[j++] = matrix[(row1 + 1) % SIZE][col1];
            encrypted_text[j++] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            encrypted_text[j++] = matrix[row1][col2];
            encrypted_text[j++] = matrix[row2][col1];
        }
    }
    encrypted_text[j] = '\0';

    printf("Encrypted message: %s\n", encrypted_text);

    return 0;
}
