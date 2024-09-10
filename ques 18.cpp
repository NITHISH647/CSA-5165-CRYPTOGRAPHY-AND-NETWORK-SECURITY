#include <stdio.h>
#include <string.h>
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};
int pc2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
int shift_schedule[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
void leftShift(unsigned char *key_half, int shift_count) {
    unsigned char shifted_half[28];
    memcpy(shifted_half, key_half + shift_count, 28 - shift_count);
    memcpy(shifted_half + 28 - shift_count, key_half, shift_count);
    memcpy(key_half, shifted_half, 28);
}
void permute(unsigned char *input, unsigned char *output, int *table, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[table[i] - 1];
    }
}

// Function to generate the 16 subkeys
void generateSubkeys(unsigned char *initial_key, unsigned char subkeys[16][48]) {
    unsigned char permuted_key[56];
    unsigned char C[28], D[28];

    permute(initial_key, permuted_key, pc1, 56);
    memcpy(C, permuted_key, 28);
    memcpy(D, permuted_key + 28, 28);

    for (int round = 0; round < 16; round++) {
        leftShift(C, shift_schedule[round]);
        leftShift(D, shift_schedule[round]);

        unsigned char combined_key[56];
        memcpy(combined_key, C, 28);
        memcpy(combined_key + 28, D, 28);

        permute(combined_key, subkeys[round], pc2, 48);
    }
}

void displaySubkeys(unsigned char subkeys[16][48]) {
    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: ", i + 1);
        for (int j = 0; j < 48; j++) {
            printf("%d", subkeys[i][j]);
        }
        printf("\n");
    }
}

int main() {
    unsigned char initial_key[64] = {
        0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1,
        1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0,
        1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1,
        1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0
    };

    unsigned char subkeys[16][48];

    generateSubkeys(initial_key, subkeys);
    displaySubkeys(subkeys);

    return 0;
}