#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 2
#define MOD 26

int mod_inverse(int a, int mod) {
    for (int x = 1; x < mod; x++) {
        if ((a * x) % mod == 1) {
            return x;
        }
    }
    return -1;
}
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}
void inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int inv_det = mod_inverse(det, MOD);

    inverse[0][0] = (matrix[1][1] * inv_det) % MOD;
    inverse[0][1] = (-matrix[0][1] * inv_det) % MOD;
    inverse[1][0] = (-matrix[1][0] * inv_det) % MOD;
    inverse[1][1] = (matrix[0][0] * inv_det) % MOD;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += MOD;
            }
        }
    }
}

int main() {
    // Known plaintext and ciphertext pairs
    char plaintext1[] = "me";
    char ciphertext1[] = "hx";
    char plaintext2[] = "at";
    char ciphertext2[] = "pk";

    int plain_matrix[MATRIX_SIZE][MATRIX_SIZE];
    int cipher_matrix[MATRIX_SIZE][MATRIX_SIZE];
    int key_matrix[MATRIX_SIZE][MATRIX_SIZE];
    int inverse_key_matrix[MATRIX_SIZE][MATRIX_SIZE];

    // Convert plaintext and ciphertext to numerical values
    for (int i = 0; i < MATRIX_SIZE; i++) {
        plain_matrix[0][i] = plaintext1[i] - 'a';
        plain_matrix[1][i] = plaintext2[i] - 'a';
        cipher_matrix[0][i] = ciphertext1[i] - 'a';
        cipher_matrix[1][i] = ciphertext2[i] - 'a';
    }

    // Compute the key matrix
    int temp_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {plain_matrix[0][0], plain_matrix[0][1]},
        {plain_matrix[1][0], plain_matrix[1][1]}
    };

    int temp_result[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        temp_result[i] = (cipher_matrix[i][0] * plain_matrix[0][0] + cipher_matrix[i][1] * plain_matrix[1][0]) % MOD;
        if (temp_result[i] < 0) temp_result[i] += MOD;
    }

    key_matrix[0][0] = temp_result[0];
    key_matrix[0][1] = temp_result[1];
    key_matrix[1][0] = temp_result[2];
    key_matrix[1][1] = temp_result[3];

    // Compute the inverse of the key matrix
    inverse_matrix(key_matrix, inverse_key_matrix);

    // Decrypting the ciphertext to verify
    char encrypted_message[] = "hxpk";
    int len = strlen(encrypted_message);

    printf("Decrypted message: ");
    for (int i = 0; i < len; i += 2) {
        int encrypted_vector[2];
        int decrypted_vector[2];

        encrypted_vector[0] = encrypted_message[i] - 'a';
        encrypted_vector[1] = encrypted_message[i + 1] - 'a';

        decrypted_vector[0] = (inverse_key_matrix[0][0] * encrypted_vector[0] + inverse_key_matrix[0][1] * encrypted_vector[1]) % MOD;
        decrypted_vector[1] = (inverse_key_matrix[1][0] * encrypted_vector[0] + inverse_key_matrix[1][1] * encrypted_vector[1]) % MOD;

        if (decrypted_vector[0] < 0) decrypted_vector[0] += MOD;
        if (decrypted_vector[1] < 0) decrypted_vector[1] += MOD;

        printf("%c%c", decrypted_vector[0] + 'a', decrypted_vector[1] + 'a');
    }

    printf("\n");

    return 0;
}
