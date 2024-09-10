#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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

unsigned long long find_mod_inv(unsigned long long e, unsigned long long phi) {
    unsigned long long t = 0, newt = 1;
    unsigned long long r = phi, newr = e;
    while (newr != 0) {
        unsigned long long quotient = r / newr;
        unsigned long long temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (t < 0) t += phi;
    return t;
}

int main() {
    unsigned long long p = 61, q = 53, n = p * q, phi = (p - 1) * (q - 1);
    unsigned long long e = 17;
    unsigned long long d = find_mod_inv(e, phi);

    printf("Public key: e = %llu, n = %llu\n", e, n);
    printf("Private key: d = %llu, n = %llu\n", d, n);

    unsigned long long plaintext = 65;
    unsigned long long ciphertext = mod_exp(plaintext, e, n);
    printf("Encrypted message: %llu\n", ciphertext);

    unsigned long long decrypted = mod_exp(ciphertext, d, n);
    printf("Decrypted message: %llu\n", decrypted);

    unsigned long long new_e = 7;
    unsigned long long new_d = find_mod_inv(new_e, phi);
    printf("New public key: e = %llu, n = %llu\n", new_e, n);
    printf("New private key: d = %llu, n = %llu\n", new_d, n);

    return 0;
}
