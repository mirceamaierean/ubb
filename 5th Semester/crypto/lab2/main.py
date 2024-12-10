# This function computes the sieve of erathostenes going towards the upper limit
def sieve_of_erathostenes(n: int):
    # Create a list of boolean values
    prime = [True for i in range(n+1)]
    # 0 and 1 are not prime numbers, so mark them as False
    prime[0] = False
    prime[1] = False
    # Update all the values that are multiple of 2s
    for i in range(4, n + 1, 2):
        prime[i] = False
    # Start from 3, and update all the values that are multiple of odd numbers
    i = 3
    # Go until the square root of n
    while i * i <= n:
        # If prime[i] is True, then it is a prime number, so we mark all the multiples as not prime numbers
        if prime[i]:
            for j in range(i * i, n + 1, i):
                prime[j] = False
        # Increase i by 2
        i += 2
    # return the values of the numbers
    return prime

n = int(input("Enter the upper limit: "))
sieve_of_erathostenes(n)

prime = sieve_of_erathostenes(n)

for i in range(1, n + 1):
    if prime[i]:
        print(i)
    # else:
    #     print(f"{i} is not a prime number")