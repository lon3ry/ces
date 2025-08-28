# Command-line Equation Solver (CES)

Here is a simple program that allows you to solve linear and quadratic
equations. Simply supply the coefficients to its command-line arguments. At
least one coefficient is required.


## Usage

```
./cqs <coefficients>
```


## Dependencies

- any C++ compiler (we use [gcc](https://gcc.gnu.org); you might need to
  modify some flags in ``Makefile`` if you want to use something else);

- [GNU Make](https://www.gnu.org/software/make);

- [Doxygen](https://doxygen.nl) (for docs).


## Building

To build the program simply run ``make``. If you want to build the docs
too, run ``make docs``.
