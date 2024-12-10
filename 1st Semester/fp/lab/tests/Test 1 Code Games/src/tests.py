import functions

def test_validation_of_input():
  '''
  Checking if some values that are valid
  1234, 1984, 1989, 1024 are all valid, so the program must return True
  '''
  assert functions.valid(1234) == True
  assert functions.valid(1984) == True
  assert functions.valid(1980) == True
  assert functions.valid(1024) == True

  # 0123 is not valid, cause it starts with 0, so the program must return False
  a = "0123"
  a = int(a)
  assert functions.valid(a) == False
  # 3435 is not valid, because 3 appears 2 times, so the program must return False
  assert functions.valid(3435) == False
  # 2001 is not valid, because 0 appears 2 times, so the program must return False
  assert functions.valid(2001) == False
  # 8888 is not valid, because 8 appears 4 times, so the program must return False
  assert functions.valid(8888) == False

def test_codes_and_runners():
  # Our secret number is 5873
  assert functions.count_codes_and_runners(9624, 5873) == (0, 0)
  assert functions.count_codes_and_runners(1234, 5873) == (0, 1)
  assert functions.count_codes_and_runners(3257, 5873) == (0, 3)
  assert functions.count_codes_and_runners(3875, 5873) == (2, 2)

def test_all():
  test_validation_of_input()
  test_codes_and_runners()