#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void extended_euclidean(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    int x1, y1;
    extended_euclidean(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}

int mod_inverse(int e, int phi_n) {
    int x, y;
    extended_euclidean(e, phi_n, &x, &y);
    if (x < 0)
        x += phi_n;
    return x;
}

int main() {
    int n = 3599;
    int e = 31;
    int p, q;qa

    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    int phi_n = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi_n);

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("phi(n) = %d\n", phi_n);
    printf("Private key d = %d\n", d);

    return 0;
}
