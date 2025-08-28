#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../polynomial_equation.hpp"
#include "../utils/common_macro.hpp"
#include "test_polynomial_equation.hpp"

void test_solve_polynomial_equation()
{
    static const polynomial_equation tests[] = {
        {
            .power = 2, .coeffs = { 1.0, -5.0, 6.0 },
            .root_count = 2, .roots = { 2.0, 3.0 }
        },
        {
            .power = 2, .coeffs = { 1.0, -5.0, 10.0 },
            .root_count = 0, .roots = { NAN, NAN }
        },
        {
            .power = 2, .coeffs = { 1.0, -10.0, 25.0 },
            .root_count = 1, .roots = { 5.0, NAN }
        },
        {
            .power = 2, .coeffs = { 0.0, -5.0, 10.0 },
            .root_count = 1, .roots = { 2.0, NAN }
        }
    };

    for (size_t i = 0; i < ARRAY_SIZE(tests); i++) {
        assert(i < ARRAY_SIZE(tests));

        struct polynomial_equation pe = tests[i];
        solve_polynomial_equation(&pe);

        if (are_polynomial_equation_sols_equal(&pe, &tests[i]))
            continue;

        fprintf(stderr, "test_solve_polynomial_equation() TEST #%lu "
                "FAILED:\n", i + 1);

        fprintf(stderr, "\tGOT %d ROOTS: ", pe.root_count);
        if (pe.root_count > 0)
            print_polynomial_equation_roots(stderr, &pe);
        else
            fputs("\n", stderr);

        fprintf(stderr, "\tEXPECTED %d ROOTS: ", tests[i].root_count);
        if (tests[i].root_count > 0)
            print_polynomial_equation_roots(stderr, &tests[i]);
        else
            fputs("\n", stderr);
    }
}
