# Solve the problem from the third set here
# The problem I choose is 13
def is_prime(n):
    '''
    This function checks if the number n is prime or not

    For sure, if n equals to 2, it is prime, being the only prime number that is even

    If n is smaller than 2, or divisible by 2, n is not a prime number

    We keep a variable val, initialized with 3, and, until the integer part of square root of n, we check
    all the odd numbers to verify if one of them divides n

    If there is such a number, then n is not a prime number
    Else, n is prime

    :param n: integer
    :return: boolean
    '''
    if (n == 2):
        return True
    if (n < 2 or n % 2 == 0):
        return False
    val = 3

    while val * val <= n:
        if n % val == 0:
            return False
        val += 2

    return True


def add_prime_numbers(left, right, prime_numbers):
    '''
    This function add to a list all the prime numbers from the interval [left, right]

    We loop in range(left, right + 1), we check if a number is prime, and if it is, we add it to the list

    :param left: integer
    :param right: integer
    :param prime_numbers: list of integers
    :return: list of integers
    '''
    for i in range(left, right + 1):
        if (is_prime(i)):
            prime_numbers.append(i)
    return prime_numbers


def count_numbers(n, prime_numbers):
    '''
    This function computes how many times each of the prime divisors appear in an array from 1 to n

    For finding this, we are looping throught the list of prime_numbers, and we add to our variable cnt the integer part from n / element. 
    :param n: integer, greater than 1
    :param prime_numbers: list of prime numbers
    :return: integer
    '''
    cnt = 1
    for element in prime_numbers:
        cnt += n // element
    return cnt


def binary_search(n):
    '''
    This function finds the greatest position i smaller than n for which all of its precedent divisors are already in the sequence

    The array is 1 2 3 2 5 2 3 7 2 3 2 5 11
    For value 11, i is equal to 10, because the 10th element of the sequence is 3, a divisor of 9, and there aren't any greater prime divisors of 9 in the sequence

    For value 12, i is equal to 12, because the 12th element of the sequence is 5, a divisor of 10, and there aren't any greater prime divisor of 10 in the sequence

    In order to find this value, we are using binary search. We start with two variales, left = 1, and right = 1. To optimize the program, we will also keepp a list of prime numbers, that is updated (if necessary) at each step during the binary search. 

    During each step, we initialize a value mid = (left + right) // 2
    If there are no prime numbers in our array, or if the left value during our step is greater than the last value in our list of prime numbers, then we call the function add_prime_numbers

    To check how many values are computed until the position x, we keep a variable current_cnt, resulted from calling the function count_numbers
    After that, we compare current_cnt with n
    If it is smaller than n, then left will have the value mid + 1. Inside this if, if current_cnt is greater than cnt, cnt will have the value of current_cnt, and val will have the value mid + 1. This represents that the nth value will be one of the prime divisors of val.
    Else, right will have the value mid - 1
    After we finish binary searching, we substract from n the value of cnt, and the reminder indicated that the number we are looking for will be the (n-cnt)th prime divisor of val 
    :param n: integer, greater than 1
    :return: integer, integer, list of integers
    '''
    left = 1
    right = n
    cnt = 0
    val = 0
    prime_numbers = []
    while left <= right:
        mid = (left + right) // 2

        if (len(prime_numbers) == 0 or left > prime_numbers[-1]):
            prime_numbers = add_prime_numbers(left, mid, prime_numbers)

        current_cnt = count_numbers(mid, prime_numbers)

        if (current_cnt < n):
            left = mid + 1
            if (current_cnt > cnt):
                cnt = current_cnt
                val = mid + 1
        else:
            right = mid - 1
    n -= cnt
    return n, val, prime_numbers


def nth_element(n):
    '''
    This functions determines the nth element of the sequence

    If n is 1, then the answer is 1

    Else, we call binary_search(n), and we will have 3 variables
    val - representing the number for which we will check the prime divisors
    n - representing that our answer is the nth prime divisor of val
    prime_numbers - a list of prime_numbers that we needed for checking find val

    We loop through the prime numbers, and if i is a divisor of val, we substract 1 from n
    If n is equal to 0, then we return the value of i 

    :param n: integer
    :return: integer
    '''
    if n == 1:
        return 1

    n, val, prime_numbers = binary_search(n)
    for i in prime_numbers:
        if val % i == 0:
            n -= 1
            if n == 0:
                return i


def solve():
    '''
    This function reads and prints the nth element of the sequence
    :param n: integer
    :return: integer
    '''
    n = int(input())
    print(nth_element(n))


solve()
