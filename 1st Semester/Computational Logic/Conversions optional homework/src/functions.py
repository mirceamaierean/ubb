# @author: Măierean Mircea
import math

def check_if_rapid_conversion_is_available(b, h):
  """
  b: integer
  h: integer
  This functions checks if the bases are 2, 4, 8 or 16
  """
  if b == 2 and (h == 4 or h == 8 or h == 16):
    return True

  if h == 2 and (b == 4 or b == 8 or b == 16):
    return True
  
  return False

def check_if_base_is_valid(b):
  """
  b: integer
  This function checks if the base is from the set {2, 3, 4, 5, 6, 7, 8, 9, 10, 16}
  """

  return (b > 1 and b < 11) or b == 16

def check_if_number_is_available_in_base_b(a, b):
  """
  a: string
  b: integer
  This function checks if the number a can be represented in base b
  """

  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']

  for dig in a:
    if dig not in list_of_digits:
      return False

    dig = list_of_digits.index(dig)
    
    if dig >= b:
      return False
  
  return True
  
def add_2_numbers_in_base_p(a, b, p):
  """
  a: string
  b: string
  p: integer
  list_of_digits contains all the suitable digits that can be found in the bases we work with
  It's easier for us to store the numbers a and b as strings, because we will work with the last digit, one by one
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
  a_index = len(a) - 1
  b_index = len(b) - 1

  '''
  We initialize a value for the remainder, that will be updated by case
  '''
  remainder = 0

  result = ""

  while a_index >= 0 or b_index >= 0:
    '''
    We take the digits, pair by pair, of our numbers. Since them are strings, we can find them by the corresponding index. From each one of the numbers, we take the digits as long as their corresponding indexes are non negative numbers
    '''

    digit_of_a = 0;
    if a_index >= 0:
      '''
      The corresponding value in base 10 is the index of our list_of_digits list
      '''
      digit_of_a = list_of_digits.index(a[a_index])
      a_index -= 1

    digit_of_b = 0;
    if b_index >= 0:
      digit_of_b = list_of_digits.index(b[b_index])
      b_index -= 1
    
    '''
    We add digits of a, digit of b, and the remainder, we compute the modulus value in base b, and the corresponding digit will be in the list_of_digits at the position of our result
    After that, the remainder has to be updated, for the future additions, and that value will be the quotient of the division by p
    EG: 
    digit_of_a = 7, digits_of_b = 8, remainder = 1, p = 16;
    current_digitst = list_of_digits[(7 + 8 + 1) % 16] = list_of_digits[16 % 16] = list_of_digits[0] = '0'
    remainder = (7 + 8 + 1) / 16 = 16 / 16 = 1
    '''
    current_digit_of_number = list_of_digits[(digit_of_a + digit_of_b + remainder) % p]
    remainder = (digit_of_a + digit_of_b + remainder) // p

    '''
    We add the digit at the front of our result
    '''
    result = current_digit_of_number + result

  '''
  If the remainder is different to 0, we have to add the digit at the front of our result
  '''
  if remainder > 0:
    current_digit_of_number = list_of_digits[remainder]
    result = current_digit_of_number + result

  return result

def greater_numbers(a, b):
  """
  a: string
  b: string
  This function checks if the first number is greater than the second one. In case it is not, the numbers are returned swapped, and we mark with a character sign = '-' that the numbers have been swapped
  """

  if len(a) > len(b):
    return a, b, ''
  if len(a) < len(b):
    return b, a, '-'
  for i in range(len(a)):
    if a[i] > b[i]:
      return a, b, ''
    if a[i] < b[i]:
      return b, a, '-'
  return a, b, ''

def sub_2_numbers_in_base_p(a, b, p):
  """
  a: string
  b: string
  p: integer
  list_of_digits contains all the suitable digits that can be found in the bases we work with
  It's easier for us to store the numbers a and b as strings, because we will work with the last digit, one by one
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']

  """
  For the case in which the first number is smaller than the second one, we swap them, and we mark in sgn that the result will be a negative number
  """
  a, b, sgn = greater_numbers(a, b)

  a_index = len(a) - 1
  b_index = len(b) - 1

  '''
  We initialize a value to mark the we borrow from the next diigts, that will be updated by case
  '''
  borrow = 0

  result = ""

  while a_index >= 0:
    '''
    We take the digits, pair by pair, of our numbers. Since them are strings, we can find them by the corresponding index. From each one of the numbers, we take the digits as long as their corresponding indexes are non negative numbers
    '''
    '''
      The corresponding value in base 10 is the index of our list_of_digits list. In case we borrow from another digit, we subtract one from our current digit
    '''
    digit_of_a = list_of_digits.index(a[a_index]) - borrow
    if digit_of_a <= 0:
      """
      If our result is smaller than 0, then it means that we will have the digit p - borrow. The value of borrow does not change
      """
      digit_of_a = p - borrow
      borrow = 1
    else:
      borrow = 0
    a_index -= 1

    digit_of_b = 0;
    if b_index >= 0:
      digit_of_b = list_of_digits.index(b[b_index])
      b_index -= 1

    if digit_of_a < digit_of_b:
      """
      In this case, we have to borrow
      """
      digit_of_a += p
      borrow = 1
    """
    The corresponding digit is found at the position digit_of_a - digit_of_b in our list
    """

    current_digit_of_number = list_of_digits[digit_of_a - digit_of_b]
    '''
    We add the digit at the front of our result
    '''
    result = current_digit_of_number + result
    
  """
  As long as our number exists, and the first digit of the result is 0, we remove it.
  """

  while result[0] == '0' and len(result) > 1:
    result = result[1:]


  """
  If necessary, we add the sign at the front of the result
  """

  result = sgn + result

  return result

def multiply_a_number_to_a_digit_in_base_p(nr, dig, p):
  """
  nr: string, 
  dig: character with which the first number is multiplied
  p: integer, the base of the number
  list_of_digits contains all the suitable digits that can be found in the bases we work with
  It's easier for us to store the number nr as string, because we will work with the last digit, one by one
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']

  index = len(nr) - 1

  """
  We find the equivalent in base 10 of our digit, being the index of the digit's value 
  """

  dig = list_of_digits.index(dig)

  result = ""
  '''
  We initialize a value for the remainder, that will be updated by case
  '''
  remainder = 0

  while index >= 0:
    '''
    We take the digits, from right to left, of our number. Since it is a string, we can find it by the corresponding index. We take the digits as long as the indexe is positive
    '''

    digit_of_nr = list_of_digits.index(nr[index])
    index -= 1
    
    """
    We multiply the current digit of the number with dig, we add the remainder from the previous step, and we find the corresponding value in list_of_digits as the reminder of the division to p. We update what we have to add for the next step
    """

    current_digit_of_number = list_of_digits[(digit_of_nr * dig + remainder) % p]
    remainder = (digit_of_nr * dig + remainder) // p

    result = current_digit_of_number + result

  """
  If we still have to add, we'll add the remainder at the front of our result
  """

  if remainder > 0:
    current_digit_of_number = list_of_digits[remainder]
    result = current_digit_of_number + result

  return result

def divide_a_number_to_a_digit_in_base_p(nr, dig, p):
  """
  nr: string, 
  dig: character with which the first number is divided
  p: integer, the base of the number
  list_of_digits contains all the suitable digits that can be found in the bases we work woth
  It's easier for us to store the number nr as string, because we will work with the last digit, one by one
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
  
  """
  We find the equivalent in base 10 of our digit, being the index of the digit's value 
  """
  dig = list_of_digits.index(dig)

  result = ""
  '''
  We initialize a value for the remainder, that will be updated by case
  '''
  remainder = 0

  for digit_of_nr in nr:
    """
    We loop through the digits from left to right, taking one each at a time.
    We find the corresponding value in base 10. 
    We compute the value remainder * p + digit_of_nr, and we divide if to dig, taking the integer part.
    We find the corresponding character of this number, and add it at the end of the result
    We update the remainder as the result of the previous operation % p
    """

    digit_of_nr = list_of_digits.index(digit_of_nr)

    current_digit_of_number = list_of_digits[(remainder * p + digit_of_nr) // dig]
    remainder = (remainder * p + digit_of_nr) % dig

    result = result + current_digit_of_number

  """
  As long as our result exists, and the first digit is 0, we remove it
  """

  while result[0] == '0' and len(result) > 1:
    result = result[1:]

  """
  We return the result, and the remainder of this division
  """

  return result, remainder

def rapid_conversion_from_base_2(a, p):
  """
  a: string, the number in base 2
  p: the base in which we want to convert to
  """
  """
  Correspondence table is a python dictionary, that has all the equivalent representations for the numbers from 0 to 16 in their corresponding base
  """

  correspondence_table = {
    2: ["0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"],
    4: ["0", "1", "2", "3", "10", "11", "12", "13", "20", "21", "22", "23", "30", "31", "32", "33"],
    8: ["0", "1", "2", "3", "4", "5", "6", "7", "10", "11", "12", "13", "14", "15", "16", "17"],
    16: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"],
  }

  a_index = len(a) - 1
  """
  k represent how many digits we have to take to form a group. 
  EG: For converting to base 8, we have to take 3 at a time 
  """
  k = int(math.log(p, 2))

  result = ""

  while a_index >= 0:
    """
    We loop through the number, from right to left, and group the digits k at a time
    """

    group = ""
    
    for _ in range(k):
      """
      As long as we have digits to take, we add them at the front of our group
      """
      if a_index >= 0:
        group = a[a_index] + group
        a_index -= 1
    
    """
    If we have to complete them, we add 0 at the front of the group
    """

    while group[0] == '0' and len(group) > 1:
      group = group[1:]
    
    """
    We find the equivalence inside the table
    """
    result = correspondence_table[p][correspondence_table[2].index(group)] + result

  return result

def rapid_conversion_to_base_2(a, p):
  """
  a: string, the number in base p
  p: the base from which we convert
  """
  """
  Correspondence table is a python dictionary, that has all the equivalent representations for the numbers from 0 to 16 in their corresponding base
  """
  correspondence_table = {
    2: ["0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"],
    4: ["0", "1", "2", "3", "10", "11", "12", "13", "20", "21", "22", "23", "30", "31", "32", "33"],
    8: ["0", "1", "2", "3", "4", "5", "6", "7", "10", "11", "12", "13", "14", "15", "16", "17"],
    16: ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"],
  }
  """
  k represent how many digits are in base 2 from base p in a group 
  EG: For converting from base 8, a digit in base 8 corresponds to 3 digits in base 2 
  """
  k = int(math.log(p, 2))
  a_index = len(a) - 1

  result = ""

  while a_index >= 0:
    """
    We loop inside our number, from left to right. As we take a digit, we find the equivalent representation in base 2
    """
    group = correspondence_table[2][correspondence_table[p].index(str(a[a_index]))]
    a_index -= 1
    """
    If the number of digits from the group does not equal k, we ad zeroes at the front until the requirement is satisfied
    """
    while len(group) < k:
      group = "0" + group
    
    result = group + result

  """
  In case we have leading zeroes at the front of our result, we erase them
  """
  while len(result) > 1 and result[0] == '0':
    result = result[1:]

  return result

def convert_using_substitution_method(a, b, h):
  """
  a: string, the number which we have to convert
  b: integer, source base
  h: integer, destination base
  list_of_digits contains all the suitable digits that can be found in the bases we work with
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
  
  """
  We find the equivalent of b in our digit representation
  """
  b = list_of_digits[b]

  index = len(a) - 1

  res = ""

  """
  Mult is a string that is going to be multiplied with different digits in order to calculate our required sum
  """
  mult = "1"

  while index >= 0:
    """
    We find the current digits of our number.
    We find the value of our current_number as the product between mult and dig in base h
    To our result, we add current_number in base h
    We update the value of mul, by the product of the current value and the corresponding digit to b
    """
    dig = a[index]
    current_number = multiply_a_number_to_a_digit_in_base_p(mult, dig, h)
    res = add_2_numbers_in_base_p(res, current_number, h)
    mult = multiply_a_number_to_a_digit_in_base_p(mult, b, h)
    index -= 1
  
  """
  In case we have leading zeroes at the front of our result, we erase them
  """
  while len(res) > 0 and res[0] == '0':
    res = res[1:]

  return res

def convert_using_successive_divisions_method(a, b, h):
  """
  a: string, the number which we have to convert
  b: integer, source base
  h: integer, destination base
  list_of_digits contains all the suitable digits that can be found in the bases we work with
  """
  list_of_digits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
  
  """
  We find the equivalent of b in our digit representation
  """
  print(b)
  b = list_of_digits[b]

  res = ""

  while a != "0":
    """
    At a step, we divide our number a to the digit b in base h
    The remainder is added at the front of the string res, and we repeat this step as long as a is greater than 0
    """
    a, remainder = divide_a_number_to_a_digit_in_base_p(a, b, h)
    res = list_of_digits[remainder] + res
  
  """
  In case we have leading zeroes at the front of our result, we erase them
  """

  while len(res) > 0 and res[0] == '0':
    res = res[1:]

  return res

def convert_using_base_10_as_intermediary_base(a, b, h):
  """
  a: string, the number we have to convert
  b: integer, the source base
  h: integer, the destination base
  """
  if b == 16:
    """
    If we have to convert from the base 16, then for sure we will convert to a base smaller than 10
    For this type of conversion, it is reccomended to use the successive divisions method
    We convert from base 16 to 10, and from base 10 to base h
    """
    result_in_base_10 = convert_using_successive_divisions_method(a, b, 10)
    return result_in_base_10, convert_using_successive_divisions_method(result_in_base_10, 10, h)
  
  if h == 16:
    """
    If we have to convert to the base 16, then for sure we will convert from a base smaller than 10
    For this type of conversion, it is reccomended to use the substitution method
    We convert from base b to 10, and from base 10 to base 16
    """
    result_in_base_10 = convert_using_substitution_method(a, b, 10)
    return result_in_base_10, convert_using_substitution_method(result_in_base_10, 10, h)
  
  """
  For this case, both of our bases are smaller than 10, so:
  b < 10 => we will convert from base b to base 10 using the substitution method
  10 < h => we will convert from base 10 to base h using the successive divisions method
  """
  result_in_base_10 = convert_using_substitution_method(a, b, 10)
  return result_in_base_10, convert_using_substitution_method(result_in_base_10, 10, h)