/// @file
///
/// Some handy utils for floating point numbers.
///
#pragma once

#include <stdio.h>

/// Checks if a < b.
bool is_less(double a, double b);

/// Checks if a = b.
bool are_equal(double a, double b);

/// Checks if a <= b.
bool is_less_or_equal(double a, double b);

/// Checks if x = 0.
bool is_zero(double x);

/// Parses the double from @p str to @p res
bool parse_double(const char str[], double *res);
