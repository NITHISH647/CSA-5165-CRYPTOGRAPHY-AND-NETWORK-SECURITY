#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    unsigned long long n, e, M, p, q;

    printf("Enter RSA modulus n: ");
    scanf("%llu", &n);
    printf("Enter public key exponent e: ");
    scanf("%llu", &e);
    printf("Enter plaintext block M: ");
    scanf("%llu", &M);

    unsigned long long gcd_result = gcd(M, n);

    if (gcd_result > 1 && gcd_result < n) {
        p = gcd_result;
        q = n / p;
        printf("Factor found: p = %llu, q = %llu\n", p, q);
    } else {
        printf("No factor found. The GCD is 1, meaning M does not share a common factor with n.\n");
    }

    return 0;
}
