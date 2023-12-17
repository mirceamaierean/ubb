# Solve the problem from the second set here
# The problem I have chosen is the 10th one
def palindrome(n):
    # This function return the palindrome of number n
    # We are keeping a value palindrome_of_n, that is initialized with 0.
    # We multiply during each step the value of palindrome_of_n with 10, after that we add the last digit of n, and we divide n by 10.
    # The process is repeated until n = 0
    palindrome_of_n = 0
    while n > 0:
        palindrome_of_n *= 10
        palindrome_of_n += n % 10
        n //= 10
    return palindrome_of_n


def print_result(n):
    # Function to print the palindrome of n
    palindrome_of_n = palindrome(n)
    print(palindrome_of_n)


def solve():
    # n must be an integer
    n = int(input())
    print_result(n)


solve()
