# Solve the problem from the first set here
# The problem I have chosen is the 4th one
def count_digits(n):
    # We initialize a list with ten elements equal to 0
    # This represents how many times the digit corresponding to the index i has appeared in our number n
    digits_cnt = [0 for element in range(10)]
    # We will increment in our list the value that has the index equal to the last digit of n
    # After that we divide n by 10.
    # The process is repeated until n = 0
    while n > 0:
        digits_cnt[n % 10] += 1
        n //= 10
    return digits_cnt


def compute_maximum_value(digits_cnt):
    # In computedValue we will store the maximum number that can be computed using the digits of n
    # We will loop in reverse through digitsCnt, and, for each index, we will add digit i to computedValue digitsCnt[i] times
    # During a step, we multiply computedValue with 10, add digit i, and substract 1 from digitsCnt[i]
    # Process is repeated until digitsCnt[i] = 0
    # This represents the largest number that can be written with the same digits as n
    computed_value = 0
    for i in range(9, -1, -1):
        while digits_cnt[i] > 0:
            computed_value *= 10
            computed_value += i
            digits_cnt[i] -= 1
    return computed_value


def print_result(n):
    # Function to print the largest number that can be created using the digits of n
    digits_cnt = count_digits(n)
    maximum_computed_value = compute_maximum_value(digits_cnt)
    print(maximum_computed_value)


def solve():
    # n must be an integer
    n = int(input())
    print_result(n)


solve()
