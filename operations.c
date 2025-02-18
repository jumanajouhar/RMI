#include <math.h>

int factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double power(double base, int exp) {
    return pow(base, exp);
}