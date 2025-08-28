#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "polynomial_equation.hpp"
#include "utils/assert.hpp"

#ifdef TEST
#include "tests/test.hpp"
#endif

static void print_help(FILE *stream, const char progname[]);
static bool parse_polynomial_coeffs_from_args(int argc,
                                              const char *const argv[],
                                              polynomial_equation *res);
static void print_polynomial_equation_sol(FILE *stream,
                                          const polynomial_equation *pe);

int main(int argc, const char *const argv[])
{
#ifdef TEST
    run_tests();
#endif

    printf("meow\n\n");

    if (argc < 2) {
        print_help(stderr, argv[0]);
        return 1;
    }

    if (argc - 1 > max_coeffs_count) {
        fprintf(stderr, "Too many args, try again.\n");
        return 1;
    }

    polynomial_equation pe = {
        .power = 0, .coeffs = { NAN, NAN, NAN },
        .root_count = 0, .roots = { NAN, NAN }
    };

    bool ok = parse_polynomial_coeffs_from_args(argc, argv, &pe);

    if (!ok) {
        fprintf(stderr, "Invalid args, try again.\n");
        return 1;
    }

    solve_polynomial_equation(&pe);
    print_polynomial_equation_sol(stdout, &pe);

    printf("\nGIT COMMIT && GIT PUSH!!!\n");

    return 0;
}

static void print_help(FILE *stream, const char progname[])
{
    assert(stream != NULL);
    assert(progname != NULL);

    fprintf(stream,
            "The polynomial equation solver\n"
            "\n"
            "Usage: %s <coefficients\n",
            progname);
}

static bool parse_polynomial_coeffs_from_args(int argc,
                                              const char *const argv[],
                                              polynomial_equation *res)
{
    assert(argv != NULL);
    POLYNOMIAL_EQUATION_ASSERT(res);

    int done = 0;

    res->power = -1;
    for (int i = 1; i < argc; i++) {
        int n = sscanf(argv[i], "%lg", &(res->coeffs[i - 1]));

        if (n != 1)
            continue;

        res->power++;
        done++;
    }

    return done > 0;
}

static void print_polynomial_equation_sol(FILE *stream,
                                          const polynomial_equation *pe)
{
    assert(stream != NULL);
    POLYNOMIAL_EQUATION_ASSERT(pe);

    switch (pe->root_count) {
    case infinite_roots:
        puts("Infinite number of roots.");
        break;
    case 0:
        puts("No real roots.");
        break;
    case 1:
        printf("One root found: %g.\n", pe->roots[0]);
        break;
    case 2:
        printf("Two roots found: %g, %g.\n", pe->roots[0], pe->roots[1]);
        break;
    default:
        printf("Unreachable branch, something went wrong :(\n");
        break;
    }
}
