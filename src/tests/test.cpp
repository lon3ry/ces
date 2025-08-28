#include "test.hpp"

#if defined(TEST_POLYNOMIAL_EQUATION) || defined(TEST_ALL)
#include "test_polynomial_equation.hpp"
#endif

void run_tests()
{
#if defined(TEST_POLYNOMIAL_EQUATION) || defined(TEST_ALL)
    test_solve_polynomial_equation();
#endif
}
