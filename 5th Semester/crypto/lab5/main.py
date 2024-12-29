# paillier encryption
import random
import math

ALPHABET = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
MAX_PRIME = 100007

# logarithmic time complexity, O(log(exp))
def rapid_exponentiation(base, exp, mod):
    result = 1
    while exp:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def validate_input(message):
    for char in message:
        if char not in ALPHABET:
            raise ValueError("Invalid character in message {}".format(message))

def L(x, n):
    return (x - 1) // n

# encryption and decryption functions
def encrypt(m, g, n):
    # select a random integer r such that 1 <= r <= n - 1
    r = random.randint(1, n - 1)
    c = (rapid_exponentiation(g, m, n * n) * rapid_exponentiation(r, n, n * n)) % (n * n)
    return c

def decrypt(c, l, n, u):
    return (L(rapid_exponentiation(c, l, n * n), n) * u) % n

def send_chars(message, n, g, l, u):
    received_message = ""
    for char in message:
        c = encrypt(ALPHABET.index(char), g, n)
        decrypted_message = decrypt(c, l, n, u)
        received_message += ALPHABET[decrypted_message]
    print(f"Received message: {received_message}")
    

def key_generation():
    while True:
        p, q = 71999, 89449
        print(f"Selected primes: {p}, {q}")
        n = p * q
        # lambda = lcm(p - 1, q - 1) = (p - 1) * (q - 1) / gcd(p - 1, q - 1)
        l = ((p - 1) * (q - 1)) // math.gcd(p - 1, q - 1)
        # select a random integer g such that g is a generator of Zn^2
        g = n + 1
        # check if mu = L(g ^ l % n ^ 2) ^ -1 % n exists
        u = L(rapid_exponentiation(g, l, n * n), n)
        try:
            inv = pow(u, -1, n)
            return n, g, l, inv
        except ValueError:
            continue

    

def paillier(message):
    try:
        validate_input(message)
    except ValueError as e:
        print(e)
        return
    # select a random private key x 
    n, g, l, u = key_generation()
    send_chars(message, n, g, l, u)


paillier("ENCRYPTED MESSAGE FOR THIS ASSIGNMENT")
paillier("PAILLIER CRYPTOSYSTEM")
paillier("CRYPTOGRAPHY IS FUN")
paillier("ENCRYPTED MESSAGE")
paillier("DECRYPTED MESSAGE")
paillier("")
paillier("DECRYPTED MESSAGE1234")
paillier("12349312")