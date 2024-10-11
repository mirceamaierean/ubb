import random


def valid(n):
  '''
  n - natural number
  return True if the number is valid, otherwise return False
  '''
  fr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

  pos = 4

  while n > 0:
    if fr[n % 10] > 0:
      return False
    fr[n % 10] = pos
    pos -= 1
    n //= 10
  
  if fr[0] == 1 or pos != 0:
    return False
    
  return True

def check_user_input(a):
  '''
  a - string, representing the value that the user has inputted
  '''
  if len(a) == 4 and valid(int(a)) == True:
    return True
  return False

def count_codes_and_runners(guess, n):
  '''
  guess - integer, natural number, being the number that the user has selected
  n - natural number, the one that has to be guessed
  The function returns the number of codes and runners that the user has guessed
  We store the positions for each digit of in a list
  We compare the digits of guess with the element in the list, and if the value is the same, then we found a code
  Else if it is different to 0, then we found a runner
  '''
  cnt_codes = 0
  cnt_runners = 0
  pos = 4
  fr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

  while n > 0:
    fr[n % 10] = pos
    n //= 10
    pos -= 1
  
  pos = 4

  while guess:
    if fr[guess % 10] > 0:
      if fr[guess % 10] == pos:
        cnt_codes += 1
      else:
        cnt_runners += 1
    pos -= 1
    guess //= 10

  return cnt_codes, cnt_runners

def generate_random_starting_value():
  '''
  This function does not have parameters
  The returned value will be generated randomly, and it will be checked to be a valid number
  '''
  while True:
    n = random.randint(1000, 9999)
    if valid(n):
      return n