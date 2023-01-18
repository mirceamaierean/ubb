# :computer: Assignment 05

## Requirements
- Use functions to: `read a complex number` from the console, `write a complex number` to the console, implement `each required functionality`.
- Functions communicate using input parameter(s) and the return statement (**DO NOT use** global variables, nested functions, the `global` or `nonlocal` keywords)
- Have two separate representations for each complex number, one using a `list` and another using a `dictionary`. Write methods to create a new complex number, to get and set each number's real and imaginary parts as well as to transform a number into its `str` representation. The program must work with both implementations, by either commenting out one of them or changing the order in which the corresponding functions are defined.
- Separate input/output functions (those using `print` and `input` statements) from those performing the calculations (see **program.py**)
- Provide the user with a menu-driven console-based user interface. Input data should be read from the console and the results printed to the console. At each step, the program must provide the user the context of the operation (do not display an empty prompt).
- Deadline is **week 7** for maximum grade, week 9 is a hard deadline.

## Problem Statement
Implement a menu-driven console application that provides the following functionalities:
1. Read a list of complex numbers (in `z = a + bi` form) from the console.
2. Display the entire list of numbers on the console.
3. Display on the console the sequence, subarray or numbers required by the properties that were assigned to you. Each student will receive one property from **Set A** and another one from **Set B**.
4. Exit the application.

**The source code will include:**
- Specifications for the functions related to point 3 above. 
- 10 complex numbers already available at program startup.

### Set A (naive implementation)
4. Length and elements of a longest subarray of numbers that contain at most 3 distinct values.

## Set B (dynamic programming implementation required)
13. The length of a longest alternating subsequence, when considering each number's modulus (e.g., given sequence [1, 3, 2, 4, 10, 6, 1], [1, 3, 2, 10] is an alternating subsequence, because 1 < 3 > 2 < 10)

## Observations
- Elements of a **subarray** are in consecutive order of their appearance in the array, while in a **subsequence**, this isn't necessarily true.
- The longest subarray/subsequence might not be unique, so determining a single one is sufficient.
- Understand and be able to explain the time and extra-space computational complexity of your implementation. 
