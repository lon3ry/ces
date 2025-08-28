/// @file
///
/// Polynomial equation solution implementation. Supports polynomials with
/// power <= 2 only.
///
#pragma once

#define POLYNOMIAL_EQUATION_ASSERT(PE)            \
    do {                                          \
        assert((PE) != NULL);                     \
        assert(is_polynomial_equation_valid(PE)); \
    } while (0)

enum {
    max_polynomial_power = 2,
    max_root_count = max_polynomial_power,
    max_coeffs_count = max_polynomial_power + 1,
    infinite_roots = -1
};

struct polynomial_equation {
    signed char power;
    double coeffs[max_coeffs_count];
    signed char root_count;
    double roots[max_root_count];
};

bool is_polynomial_equation_valid(const polynomial_equation *pe);

/// Solves the polynomial equation.
/// @note It normalizes the equation before solving it.
void solve_polynomial_equation(polynomial_equation *pe);

/// Normalizes the polynomial_equation. Shifts all leading zero while
/// lowering the power to make it correct and sorts the roots ascending.
void normalize_polynomial_equation(polynomial_equation *pe);

/// Check if polynomial equation solutions are equal.
/// @note It only checks used roots.
bool are_polynomial_equation_sols_equal(const polynomial_equation *pe1,
                                        const polynomial_equation *pe2);

#if defined(DEBUG) || defined(TEST_POLYNOMIAL) || defined(TEST_ALL)
#include <stdio.h>

void print_polynomial_equation_roots(FILE *stream,
                                     const polynomial_equation *pe);
#endif
