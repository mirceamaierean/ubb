import random
P = int(1e9 + 7) # 1000000007 => G = 5
G = int(5)

ALPHABET = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
ALPHABET_SIZE = len(ALPHABET)

def text_to_number(text):
    return int(''.join(str(ALPHABET.index(char)).zfill(2) for char in text))

def number_to_text(number):
    number_str = str(number)
    if len(number_str) % 2 != 0:
        number_str = '0' + number_str
    return ''.join(ALPHABET[int(number_str[i:i+2])] for i in range(0, len(number_str), 2))

# function that converts a string to a number in base 27
def get_message_as_number(message):
    number = 0
    for i in range(len(message)):
        number += ALPHABET.index(message[i]) * (27 ** i)
    return number

# from a number in base 27, we reconvert to find a proper string
def get_message_as_string(number):
    message = ""
    while number > 0:
        message += ALPHABET[number % 27]
        number //= 27
    return message[::-1]

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
# https://www.geeksforgeeks.org/elgamal-encryption-algorithm/
# https://medium.com/@MatinGhanbari/the-elgamal-encryption-algorithm-dc1dc4442281
def encrypt(message, x):
    h = rapid_exponentiation(G, x, P)
    k = random.randint(1, P - 2)
    c1 = rapid_exponentiation(G, k, P)
    # m = text_to_number(message)
    m = message
    c2 = (m * rapid_exponentiation(h, k, P)) % P
    return c1, c2

def decrypt(c1, c2, x):
    s = rapid_exponentiation(c1, x, P)
    # m is the modular inverse
    m = rapid_exponentiation(s, P - 2, P)
    message = (c2 * m) % P
    # return number_to_text(message)
    return message

print(len(ALPHABET))
x = random.randint(1, P - 2)
# message = "MESAJ"
message = 123124343
c1, c2 = encrypt(message, x)
print(f"Encrypted message: {c1}, {c2}")
decrypted_message = decrypt(c1, c2, x)
print(f"Decrypted message: {decrypted_message}")


