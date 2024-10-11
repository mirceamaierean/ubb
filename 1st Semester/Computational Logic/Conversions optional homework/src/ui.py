# @author: Măierean Mircea

import functions

def print_ui():
  print("Author: Mircea Măierean")
  while True:
    print("In order to perform an actions, please enter the index of the command you want to execute!")
    print("1. Convertion of two numbers from a base to another")
    print("2. Perform operations with numbers")
    print("3. Close the program")
    
    option = int(input("Select an option: "))

    if option == 1:
      print("Conversion Methods available")
      print ("1. Convert using base 10 as an intermediary base")
      print ("2. Convert using rapid conversions")
      print ("3. Convert using substitution method")
      print ("4. Convert using successive divisions method")

      option = int(input("Select an option: "))
      nr = input("What's the number you want to convert? ").upper()
      b = int(input("From which base you want to convert? "))
      h = int(input("To which base you want to convert? "))

      if option == 1:  
        if functions.check_if_base_is_valid(b) and functions.check_if_base_is_valid(h) and functions.check_if_number_is_available_in_base_b(nr, b):
          nr_in_10, nr_in_h = functions.convert_using_base_10_as_intermediary_base(nr, b, h)
          print(f"The number {nr} in base {b} is {nr_in_10} in base 10")
          print(f"The number {nr_in_10} in base 10 is {nr_in_h} in base {h}")
        else:
          print ("Your input is not valid!")

      elif option == 2:  
        if functions.check_if_base_is_valid(b) and functions.check_if_base_is_valid(h) and functions.check_if_rapid_conversion_is_available(b, h) and functions.check_if_number_is_available_in_base_b(nr, b):
          if b == 2:
            res = functions.rapid_conversion_from_base_2(nr, h)
          else:
            res = functions.rapid_conversion_to_base_2(nr, b)
          print(f"The number {nr} in base {b} is {res} in base {h}")
        else:
          print ("Your input is not valid!")

      elif option == 3:  
        print("For this method, the source base has to be smaller than the destionation base")
        if functions.check_if_base_is_valid(b) and functions.check_if_base_is_valid(h) and b < h and functions.check_if_number_is_available_in_base_b(nr, b):
          res = functions.convert_using_substitution_method(nr, b, h)
          print(f"The number {nr} in base {b} is {res} in base {h}")
        else:
          print ("Your input is not valid!")
            
      elif option == 4:  
        print("For this method, the source base has to be greater than the destionation base")
        if functions.check_if_base_is_valid(b) and functions.check_if_base_is_valid(h) and b > h and functions.check_if_number_is_available_in_base_b(nr, b):
          res = functions.convert_using_successive_divisions_method(nr, h, b)
          print(f"The number {nr} in base {b} is {res} in base {h}")
        else:
          print ("Your input is not valid!")
        
      else:
        print("Your input does not match any of the available options. Try again")
      
    elif option == 2:
      print ("Operations available")
      print ("1. Add 2 numbers in base p")
      print ("2. Subtract 2 numbers in base p")
      print ("3. Multiply a number to a digit in base p")
      print ("4. Divide a number to a digit in base p")
      
      option = int(input("Select an option: "))

      b = int(input("In which base would you like to perform the operations? "))
      nr1 = input("What's the first number of this operation? ").upper()
      nr2 = input("What's the second number of this operation? ").upper()
      
      if option == 1:
        if functions.check_if_base_is_valid(b) and functions.check_if_number_is_available_in_base_b(nr1, b) and functions.check_if_number_is_available_in_base_b(nr2, b):
          res = functions.add_2_numbers_in_base_p(nr1, nr2, b)
          print (f"{nr1}+{nr2} in base {b} is equal to {res}")
        else:
          print ("Your input is not valid!")

      elif option == 2:
        if functions.check_if_base_is_valid(b) and functions.check_if_number_is_available_in_base_b(nr1, b) and functions.check_if_number_is_available_in_base_b(nr2, b):
          res = functions.sub_2_numbers_in_base_p(nr1, nr2, b)
          print (f"{nr1}-{nr2} in base {b} is equal to {res}")
        else:
          print ("Your input is not valid!")

      elif option == 3:
        if len(nr2) == 1 and functions.check_if_base_is_valid(b) and functions.check_if_number_is_available_in_base_b(nr1, b) and functions.check_if_number_is_available_in_base_b(nr2, b):
          res = functions.multiply_a_number_to_a_digit_in_base_p(nr1, nr2, b)
          print (f"{nr1} * {nr2} in base {b} is equal to {res}")
        else:
          print ("Your input is not valid!")

      elif option == 4:
        if len(nr2) == 1 and functions.check_if_base_is_valid(b) and functions.check_if_number_is_available_in_base_b(nr1, b) and functions.check_if_number_is_available_in_base_b(nr2, b):
          res, remainder = functions.divide_a_number_to_a_digit_in_base_p(nr1, nr2, b)
          print (f"{nr1}/{nr2} in base {b} is equal to {res}")
          print (f"The remainder of this operation is {remainder}")
        else:
          print ("Your input is not valid!")
      
      else:
        print("Your input does not match any of the available options. Try again")  
    elif option == 3:
      print ("Goodbye!")
      return
    
    option = input("Do you want to perform another task? [Y/N]").upper()
    if option == "N":
      print ("Goodbye!")
      return
