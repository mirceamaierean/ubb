# apply the generalized algorithm of fermat
import math


def find_non_trivial_factor(n):
    for k in range(1, n):
        t0 = int(math.sqrt(k * n))
        for t in range(t0 + 1, t0 + 5):
            x = math.sqrt(t * t - k * n)
            if x == int(x):
                if (t - int(x)) % k == 0 and int((t - int(x)) / k) > 1:
                    return int((t - int(x)) / k), int((t + int(x)))
                elif (t + int(x)) % k == 0 and int((t + int(x)) / k) > 1:
                    return int((t - int(x))), int((t + int(x)) / k) 
            
    return None, None

n = int(input("Enter the value of n: "))

t0, x = find_non_trivial_factor(n)

print("Trivial factors are ", t0, x)