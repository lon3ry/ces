#include <math.h>
#include <assert.h>
#include <stddef.h>

#include "utils/float_utils.hpp"
#include "utils/common_macro.hpp"
#include "polynomial_equation.hpp"

bool are_polynomial_coeffs_valid(const polynomial_equation *pe);
bool are_polynomial_roots_valid(const polynomial_equation *pe);

bool is_polynomial_equation_valid(const polynomial_equation *pe)
{
    assert(pe != NULL);

    if (pe->power < 0 || pe->power > max_polynomial_power)
        return false;

    if (!are_polynomial_coeffs_valid(pe))
        return false;

    if (pe->root_count > 0 && !are_polynomial_roots_valid(pe))
        return false;

    return true;
}

bool are_polynomial_coeffs_valid(const polynomial_equation *pe)
{
    assert(pe != NULL);

    if (pe->power == 0)
        return true;

    for (int i = 0; i <= pe->power; i++) {
        assert(0 <= i && i <= pe->power);
        if (!isfinite(pe->coeffs[i]))
            return false;
    }

    return true;
}

bool are_polynomial_roots_valid(const polynomial_equation *pe)
{
    assert(pe != NULL);

    for (int i = 0; i < pe->root_count; i++) {
        assert(0 <= i && i < pe->root_count);
        if (!isfinite(pe->roots[i]))
            return false;
    }
    return true;
}

static void solve_const_equation(polynomial_equation *pe);
static void solve_linear_equation(polynomial_equation *pe);
static void solve_quadratic_equation(polynomial_equation *pe);

void solve_polynomial_equation(polynomial_equation *pe)
{
    POLYNOMIAL_EQUATION_ASSERT(pe);

    normalize_polynomial_equation(pe);

    switch(pe->power) {
    case 0:  solve_const_equation(pe);     break;
    case 1:  solve_linear_equation(pe);    break;
    case 2:  solve_quadratic_equation(pe); break;
    default: abort();
    }
}

static void solve_const_equation(polynomial_equation *pe)
{
    // Note that here we don't check if the first coefficient is zero,
    // because it's perfectly okay for constant equation.
    POLYNOMIAL_EQUATION_ASSERT(pe);

    if (is_zero(pe->coeffs[0]))
        pe->root_count = infinite_roots;
    else
        pe->root_count = 0;
}

#define SOLVE_POLYNOMIAL_EQUATION_ASSERT(PE) \
    do {                                     \
        POLYNOMIAL_EQUATION_ASSERT(PE);      \
        assert(!is_zero((PE)->coeffs[0]));   \
    } while (0)

static void solve_linear_equation(polynomial_equation *pe)
{
    SOLVE_POLYNOMIAL_EQUATION_ASSERT(pe);

    pe->roots[0] = -pe->coeffs[1] / pe->coeffs[0];
    pe->root_count = 1;
}

static void sort_double_array(double a[], int n);

static void solve_quadratic_equation(polynomial_equation *pe)
{
    SOLVE_POLYNOMIAL_EQUATION_ASSERT(pe);

    if (is_zero(pe->coeffs[0]) && is_zero(pe->coeffs[1]) &&
        is_zero(pe->coeffs[2]))
    {
        pe->root_count = 0;
        return;
    }

    double d = pe->coeffs[1] * pe->coeffs[1] - 4 * pe->coeffs[0] *
               pe->coeffs[2];

    assert(isfinite(d));

    if (is_zero(d)) {
        pe->roots[0]   = -pe->coeffs[1] / (2 * pe->coeffs[0]);
        pe->root_count = 1;
        return;
    }

    if (is_less(d, 0.0)) {
        pe->root_count = 0;
        return;
    }

    d = sqrt(d);

    if (is_zero(pe->coeffs[2])) {
        pe->coeffs[0]  = pe->coeffs[1] / pe->coeffs[0];
        pe->root_count = 1;
        return;
    }

    pe->roots[0] = (-pe->coeffs[1] - d) / (2 * pe->coeffs[0]);
    pe->roots[1] = (-pe->coeffs[1] + d) / (2 * pe->coeffs[0]);
    pe->root_count = 2;
    sort_double_array(pe->roots, pe->root_count);
}

static void sort_double_array(double a[], int n)
{
    assert(a != NULL);

    for (int i = 0; i < n; i++) {
        assert(0 <= i && i < n);
        for (int j = i + 1; j < n; j++) {
            assert(0 <= j && j < n);
            if (is_less_or_equal(a[i], a[j]))
                continue;
            double tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
}

static void dec_polynomial_power(polynomial_equation *pe);

void normalize_polynomial_equation(polynomial_equation *pe)
{
    POLYNOMIAL_EQUATION_ASSERT(pe);

    while (pe->power > 0 && is_zero(pe->coeffs[0]))
        dec_polynomial_power(pe);

    sort_double_array(pe->roots, pe->root_count);
}

static void dec_polynomial_power(polynomial_equation *pe)
{
    POLYNOMIAL_EQUATION_ASSERT(pe);

    for (int i = 0; i < pe->power; i++) {
        assert(0 <= i && i < pe->power);
        pe->coeffs[i] = pe->coeffs[i + 1];
    }
    pe->power--;
}

bool are_polynomial_equation_sols_equal(const polynomial_equation *pe1,
                                        const polynomial_equation *pe2)
{
    POLYNOMIAL_EQUATION_ASSERT(pe1);
    POLYNOMIAL_EQUATION_ASSERT(pe2);

    if (pe1->root_count != pe2->root_count)
        return false;

    for (int i = 0; i < pe1->root_count; i++) {
        assert(0 <= i && i < pe1->root_count);
        if (!are_equal(pe1->roots[i], pe2->roots[i]))
            return false;
    }

    return true;
}

#if defined(DEBUG) || defined(TEST_POLYNOMIAL) || defined(TEST_ALL)
#include <stdio.h>

void print_polynomial_equation_roots(FILE *stream,
                                     const polynomial_equation *pe)
{
    for (int i = 0; i < pe->root_count; i++) {
        assert(0 <= i && i < pe->root_count);
        fprintf(stream, "%g%s", pe->roots[i], (i < pe->root_count - 1) ?
            ", " : "\n");
    }
}
#endif
