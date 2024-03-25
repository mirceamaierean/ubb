def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


def lcm(l):
    if len(l) == 1:
        return l[0]
    return l[0] * lcm(l[1:]) // gcd(l[0], lcm(l[1:]))


l = [2, 3, 4, 6]

print(lcm(l))
