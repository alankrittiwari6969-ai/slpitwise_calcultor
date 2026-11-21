#include <math.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT
#endif

#define MAX_PEOPLE 10

/* ---------- Basic calculator ---------- */
EXPORT double calc_basic(int op, double a, double b) {
    switch (op) {
        case 1: return a + b;
        case 2: return a - b;
        case 3: return a * b;
        case 4: return (b == 0) ? NAN : a / b;
        default: return NAN;
    }
}

/* ---------- Percentage, interest ---------- */
EXPORT double calc_percentage(double value, double percent) {
    return value * percent / 100;
}

EXPORT double calc_interest(double principal, double rate, double years) {
    return principal * rate * years / 100;
}

/* ---------- EMI ---------- */
EXPORT double calc_emi(double principal, double annual_rate, double months) {
    if (principal <= 0 || months <= 0) {
        return NAN;
    }
    double r = annual_rate / 12 / 100;
    if (r == 0) {
        return principal / months;
    }
    double factor = pow(1 + r, months);
    return principal * r * factor / (factor - 1);
}

/* ---------- Factorial (recursion) ---------- */
static double factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

EXPORT double calc_factorial(int n) {
    if (n < 0 || n > 20) {
        return NAN;
    }
    return factorial(n);
}

/* ---------- Temperature ---------- */
EXPORT double calc_temperature(int mode, double t) {
    if (mode == 1) return t * 9 / 5 + 32;
    if (mode == 2) return (t - 32) * 5 / 9;
    return NAN;
}

/* ---------- Splitwise ---------- */
EXPORT int calc_splitwise(const double *paid, int n, double *balance, double *out) {
    if (n < 2 || n > MAX_PEOPLE) {
        return -1;
    }

    double total = 0;
    for (int i = 0; i < n; i++) {
        total += paid[i];
    }
    double share = total / n;

    double left[MAX_PEOPLE];
    for (int i = 0; i < n; i++) {
        balance[i] = paid[i] - share;
        left[i] = balance[i];
    }

    int count = 0;
    while (1) {
        int maxIdx = 0, minIdx = 0;
        for (int i = 1; i < n; i++) {
            if (left[i] > left[maxIdx]) maxIdx = i;
            if (left[i] < left[minIdx]) minIdx = i;
        }

        if (left[maxIdx] < 0.01) break;

        double amount = left[maxIdx];
        if (-left[minIdx] < amount) amount = -left[minIdx];

        out[count * 3]     = minIdx;
        out[count * 3 + 1] = maxIdx;
        out[count * 3 + 2] = amount;
        count++;

        left[maxIdx] -= amount;
        left[minIdx] += amount;
    }
    return count;
}
