#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26

int main() {
    int key_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24},
        {1, 13}
    };

    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    int len = strlen(plaintext);

    int plaintext_vector[2];
    int encrypted_vector[2];
    int decrypted_vector[2];

    printf("Encrypted message: ");
    for (int i = 0; i < len; i += 2) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext_vector[0] = plaintext[i] - 'a';
        } else {
            plaintext_vector[0] = 0;
        }

        if (i + 1 < len && plaintext[i + 1] >= 'a' && plaintext[i + 1] <= 'z') {
            plaintext_vector[1] = plaintext[i + 1] - 'a';
        } else {
            plaintext_vector[1] = 0;
        }

        encrypted_vector[0] = (key_matrix[0][0] * plaintext_vector[0] + key_matrix[0][1] * plaintext_vector[1]) % MOD;
        encrypted_vector[1] = (key_matrix[1][0] * plaintext_vector[0] + key_matrix[1][1] * plaintext_vector[1]) % MOD;

        if (encrypted_vector[0] < 0) encrypted_vector[0] += MOD;
        if (encrypted_vector[1] < 0) encrypted_vector[1] += MOD;

        printf("%c%c", encrypted_vector[0] + 'a', encrypted_vector[1] + 'a');
    }

    printf("\n");

    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24},
        {1, 13}
    };

    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
    int inv_det = -1;
    for (int x = 1; x < MOD; x++) {
        if ((det * x) % MOD == 1) {
            inv_det = x;
            break;
        }
    }

    int inverse_matrix[MATRIX_SIZE][MATRIX_SIZE];
    inverse_matrix[0][0] = (matrix[1][1] * inv_det) % MOD;
    inverse_matrix[0][1] = (-matrix[0][1] * inv_det) % MOD;
    inverse_matrix[1][0] = (-matrix[1][0] * inv_det) % MOD;
    inverse_matrix[1][1] = (matrix[0][0] * inv_det) % MOD;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse_matrix[i][j] < 0) {
                inverse_matrix[i][j] += MOD;
            }
        }
    }

    printf("Decrypted message: ");
    for (int i = 0; i < len; i += 2) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext_vector[0] = plaintext[i] - 'a';
        } else {
            plaintext_vector[0] = 0;
        }

        if (i + 1 < len && plaintext[i + 1] >= 'a' && plaintext[i + 1] <= 'z') {
            plaintext_vector[1] = plaintext[i + 1] - 'a';
        } else {
            plaintext_vector[1] = 0;
        }

        decrypted_vector[0] = (inverse_matrix[0][0] * plaintext_vector[0] + inverse_matrix[0][1] * plaintext_vector[1]) % MOD;
        decrypted_vector[1] = (inverse_matrix[1][0] * plaintext_vector[0] + inverse_matrix[1][1] * plaintext_vector[1]) % MOD;

        if (decrypted_vector[0] < 0) decrypted_vector[0] += MOD;
        if (decrypted_vector[1] < 0) decrypted_vector[1] += MOD;

        printf("%c%c", decrypted_vector[0] + 'a', decrypted_vector[1] + 'a');
    }

    printf("\n");

    return 0;
}
