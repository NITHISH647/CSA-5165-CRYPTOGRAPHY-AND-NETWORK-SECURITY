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
    unsigned long long a = 5; // Public base
    unsigned long long q = 23; // Public modulus

    unsigned long long alice_secret = 6; // Alice's secret number
    unsigned long long bob_secret = 15;  // Bob's secret number

    unsigned long long alice_public = mod_exp(a, alice_secret, q);
    unsigned long long bob_public = mod_exp(a, bob_secret, q);

    unsigned long long alice_shared = mod_exp(bob_public, alice_secret, q);
    unsigned long long bob_shared = mod_exp(alice_public, bob_secret, q);

    printf("Alice's public value: %llu\n", alice_public);
    printf("Bob's public value: %llu\n", bob_public);
    printf("Alice's computed shared key: %llu\n", alice_shared);
    printf("Bob's computed shared key: %llu\n", bob_shared);

    return 0;
}
