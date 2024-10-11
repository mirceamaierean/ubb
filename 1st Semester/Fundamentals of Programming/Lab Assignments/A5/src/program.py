#
# Write the implementation for A5 in this file
#

# 
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

from cmath import sqrt
import random


def create_complex_number(real, imag):
    return [real, imag]
 
 
def get_real(c):
    return c[0]
 
 
def get_imag(c):
    return c[1]

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

# def create_complex_number(real, imag):
#     return {'real': real, 'imag': imag}


# def get_real(c):
#     return c['real']


# def get_imag(c):
#     return c['imag']

#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def generate_random_complex_numbers():
    l = []
    for i in range(10):
        l.append(create_complex_number(random.randint(1, 100), random.randint(1, 100)))
    return l

def get_modulus(c):
    real = get_real(c)
    img = get_imag(c)
    return real * real + img * img

def get_list_of_modulus(l):
    list_of_modulus = []
    
    for c in l:
        list_of_modulus.append(get_modulus(c))
    
    return list_of_modulus

def longest_alternating_subsequence(L):
    l = get_list_of_modulus(L)

    inc = 1
    dec = 1
 
    for i in range(1, len(l)):
        if l[i] > l[i - 1]:
            inc = dec + 1
 
        elif l[i] < l[i - 1]:
            dec = inc + 1
    return max(inc, dec)

def number_of_different_elements(l):
    unique_list = []
    for el in l:
        if not el in unique_list:
            unique_list.append(el);
    return len(unique_list)

def solve_naive(l):
    max_seq = []
    for i in range(len(l)):
        de = []
        for j in range(i, len(l)):
            de.append(l[j])
            if number_of_different_elements(de) <= 3 and len(de) > len(max_seq):
                max_seq = de.copy()
    return max_seq
        
#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def option_1(l):
    n = int(input("Number of complex numbers: "))
    for i in range(n):
        real = int(input("Real part of the number: "))
        imag = int(input("Imaginary part of the number: "))
        c = create_complex_number(real, imag)
        l.append(c)
    return l

def print_menu():
    print("1. Read a complex number")
    print("2. Print the list of complex numbers")
    print("3. Display the length and elements of a longest subarray of numbers that contain at most 3 distinct values and the length of a longest alternating subsequence, when considering each number's modulus.")
    print ("4. Exit the aplication")

def print_naive_solution(l):
    print("Property A: Length and elements of a longest subarray of numbers that contain at most 3 distinct values")
    print("The length of this sequence is", (len(l)))
    print("The sequence is", l)

def print_dp_solution(l):
    print("Property B: The length of the longest alternating subsequence")
    print("The length of this sequence is", longest_alternating_subsequence(l))


def ui_section():
    print_menu()
    n = int(input("Choose an option: "))
    l = generate_random_complex_numbers();
    while True:
        if n == 1:
            l = option_1(l)
        elif n == 2:
            for el in l:
                print(el)
        elif n == 3:
            print_naive_solution(solve_naive(l))
            print_dp_solution(l)
        elif n == 4:
            print("See you soon :)")
            break
        else:
            n = int(input("This is not a valid value, try again: "))
            continue
        n = int(input("Operation succeded, perform another action: "))
        

if __name__ == "__main__":
    ui_section()



