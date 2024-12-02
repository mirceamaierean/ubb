import random

ALPHABET = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
MAX_PRIME = 1000007

# logarithmic time complexity, O(log(exp))
def rapid_exponentiation(base, exp, mod):
    result = 1
    while exp:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

# encryption and decryption functions
def encrypt(message, x, P, G):
    # compute h = G^x mod P
    h = rapid_exponentiation(G, x, P)
    # select a random integer k
    k = random.randint(1, P - 2)
    # compute c1 = G^k mod P
    c1 = rapid_exponentiation(G, k, P)
    # m = text_to_number(message)
    m = message
    # compute m * h^k mod P
    c2 = (m * rapid_exponentiation(h, k, P)) % P
    return c1, c2

def decrypt(c1, c2, x, P, G):
    # compute s = c1^x mod P
    s = rapid_exponentiation(c1, x, P)
    # m is the modular inverse, and because P is a prime number, we can use the Fermat's Little Theorem saying that a^(p-1) = 1 mod p    
    m = rapid_exponentiation(s, P - 2, P)
    # get the original message
    message = (c2 * m) % P
    return message

def send_chars(message, x, P, G):
    received_message = ""
    for char in message:
        # print(f"Sending character: {char}")
        c1, c2 = encrypt(ALPHABET.index(char), x, P, G)
        # print(f"Encrypted message: {c1}, {c2}")
        decrypted_message = decrypt(c1, c2, x, P, G)
        # print(f"Decrypted message: {decrypted_message}")
        received_message += ALPHABET[decrypted_message]
    print(f"Received message: {received_message}")

def check_generator(prime, generator): 
    existing = [False] * (prime + 1)
    val = 1
    for _ in range(1, prime):
        val = (val * generator) % prime
        if existing[val]:
            return False
        existing[val] = True
    return True
    

def get_random_prime_and_generator():
    sieve = [True] * (MAX_PRIME + 1)
    sieve[0] = sieve[1] = False
    primes = []
    for i in range(2, MAX_PRIME):
        if sieve[i]:
            for j in range(i * i, MAX_PRIME, i):
                sieve[j] = False
    for i in range(100, MAX_PRIME):
        if sieve[i]:
            primes.append(i)
    while True:
        random_prime = random.choice(primes)
        for i in range(2, random_prime):
            if check_generator(random_prime, i):
                return random_prime, i
      

def el_gamal(message):
    # select a random private key x
    
    P, G = get_random_prime_and_generator()
    print(f"Prime number: {P}")
    print(f"Generator: {G}")
    x = random.randint(1, P - 2)
    send_chars(message, x, P, G)


el_gamal("ENCRYPTED MESSAGE FOR THIS ASSIGNMENT")
el_gamal("EL GAMAL CRYPTOGRAPHY")
el_gamal("CRYPTOGRAPHY IS FUN")
el_gamal("ENCRYPTED MESSAGE")
el_gamal("DECRYPTED MESSAGE")
el_gamal("ENCRYPTED MESSAGE")
el_gamal("DECRYPTED MESSAGE")