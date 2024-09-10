#include <stdio.h>
#include <math.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    unsigned long long n = 3233; // Example modulus (n = 61 * 53)
    unsigned long long e = 17; // Example public exponent
    unsigned long long plaintext[] = {0, 18, 14}; // Example plaintext: A, S, O
    unsigned long long ciphertext[3];

    for (int i = 0; i < 3; i++) {
        ciphertext[i] = mod_exp(plaintext[i], e, n);
        printf("Encrypted character %llu: %llu\n", plaintext[i], ciphertext[i]);
    }

    return 0;
}
