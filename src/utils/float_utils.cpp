#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "float_utils.hpp"

static const double float_error = 1e-6;

bool is_less(double a, double b)
{
    return a - b < -float_error;
}

bool are_equal(double a, double b)
{
    return fabs(a - b) <= float_error;
}

bool is_less_or_equal(double a, double b)
{
    return is_less(a, b) || are_equal(a, b);
}

bool is_zero(double x)
{
    return are_equal(x, 0.0);
}

bool parse_double(const char str[], double *res)
{
    assert(str != NULL);
    assert(res != NULL);

    int ret = sscanf(str, "%lf", res);
    return ret == 1;
}
