import functions

def print_ui():
  n = functions.generate_random_starting_value()

  while True:
    a = input("What is your guess: ")
  
    if a == "8086":
      print ("The number you have to guess is", n)
  
    else:
      if functions.check_user_input(a) == False:
        print("Your input is not valid. You lost!")
        return
  
      a = int(a)

      if a == n:
        print ("You have guessed the right number. Congratulations!")
        return
        
      cnt_codes, cnt_rullers = functions.count_codes_and_runners(a, n)
      print ("The number of codes reported is", cnt_codes)
      print ("The number of runners reported is", cnt_rullers)