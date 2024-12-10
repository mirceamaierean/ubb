#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#

import functions

def process_command_add(command, expense_types, apartments):
  if len(command) != 4:
    print("This is an invalid command. The form of this command should be add <apartment> <type> <amount>")
    return apartments
  try:  
    command[1] = int(command[1])
  except ValueError:
    print("The value of the apartment must be a natural number")
    return apartments 
  if command[2] not in expense_types:
    print("This is not a valid expense. Please try again")
    return apartments 
  try:
    command[3] = int(command[3])
  except ValueError:
    print("The amount must be a natural number")
    return apartments 

  apartments = functions.modify_expense(apartments, int(command[1]), command[2], int(command[3]))

  return apartments

def process_command_remove(command, expense_types, list_of_operations, apartments):
  if len(command) == 2:
    try:
      command[1] = int(command[1])
    except ValueError:
      if command[1] not in expense_types:
        print("This is not a valid expense. Please try again")
        return apartments, list_of_operations

      apartments, op = functions.delete_apartments_with_expense_type(command[1], apartments)
      list_of_operations.append(op)
      return apartments, list_of_operations
    
    apartments, op = functions.delete_apartments_between_indexes(int(command[1]), int(command[1]), apartments)
    list_of_operations.append(op)

    return apartments, list_of_operations


  elif len(command) == 4:
    if command[2] != "to":
      print("This is not a valid command. Please try again")
      return apartments, list_of_operations

    try:
      command[1] = int(command[1])
    except ValueError:
      print("The value of the apartment must be a natural number")
      return apartments, list_of_operations

    try:
      command[3] = int(command[3])
    except ValueError:
      print("The value of the apartment must be a natural number")
      return apartments, list_of_operations

    apartments, op = functions.delete_apartments_between_indexes(int(command[1]), int(command[3]), apartments)
    list_of_operations.append(op)
    return apartments, list_of_operations
  
  else:
    print ("This is not a valid command. Try again")
    return apartments, list_of_operations

def process_command_replace(command, expense_types, apartments, list_of_operations):
  op = []
  if len(command) == 5:
    try:
      command[1] = int(command[1])
    except ValueError:
      print("The value of the apartment must be a natural number")
      return

    try:
      command[4] = int(command[4])
    except ValueError:
      print("The value of the amount must be a natural number")
      return

    if command[2] not in expense_types:
        print("This is not a valid expense. Please try again")
        return

    if command[3] != "with":
        print("This is not a valid expense. Please try again")
        return

    apartments, op = functions.replace_amounf_of_expense_for_ap(apartments, int(command[1]), command[2], int(command[4]))
    list_of_operations.append(op)
    return apartments, list_of_operations

  else:
    print ("This is not a valid command. Try again")

def list_apartments(apartments):
  print(*apartments, sep = "\n")

def process_command_display(command, apartments):
  if len(command) == 1:
    list_apartments(apartments)
  signs = ["=", "<", ">"]
  if len(command) == 2:
    try:
      command[1] = int(command[1])
    except ValueError:
      print("The value of the apartment must be a natural number")
      return
    list_apartments(functions.all_expenses_of_apartment(apartments, int(command[1])))
  elif len(command) == 3:
    try:
      command[2] = int(command[2])
    except ValueError:
      print("The value of the amount must be a natural number")
      return
    try:
      index = signs.index(command[1])
    except ValueError:
      print("The comparrison sign is not valid")
      return
    list_apartments(functions.find_apartments_that_satisfy_the_condition(apartments, int(command[2]), index))

def process_command_filter(command, expense_types, apartments, list_of_operations):
  op = []
  if len(command) == 2:
    try:
      command[1] = int(command[1])
    except ValueError:
      if (command[1] not in expense_types):
        print("Invalid input. Please try again")
        return apartments, list_of_operations
      apartments, op = functions.filter_apartment_by_type(apartments, command[1])
      list_of_operations.append(op)
      return apartments, list_of_operations

    apartments, op = functions.filter_apartment_by_amount(apartments, int(command[1]))
    list_of_operations.append(op)
    return apartments, list_of_operations
  else:
    print("Invalid command. Please try again")
    return apartments, list_of_operations

def process_command_undo(command, apartments, list_of_operations):
  if len(command) != 1:
    print("This is not a valid command")
    return apartments, list_of_operations
  
  if len(list_of_operations) == 0:
    print("The list of operations is empty. Please perform an operation before trying to undo them")
    return apartments, list_of_operations

  apartments = functions.undo_operations(list_of_operations[-1], apartments)
  list_of_operations.pop()

  return apartments, list_of_operations


def process_command(command, apartments, list_of_operations):
  commands = ["add", "remove", "replace", "list", "filter", "undo"]

  expense_types = ["gas", "water", "electricity", "heating", "water", "other"]
  
  if command[0] not in commands:
    print("This is an invalid command. Please try again")
    return apartments, list_of_operations

  if command[0] == "add":
    apartments = process_command_add(command, expense_types, apartments)

  elif command[0] == "remove":
    apartments, list_of_operations = process_command_remove(command, expense_types, list_of_operations, apartments)
  
  elif command[0] == "replace":
    apartments, list_of_operations = process_command_replace(command, expense_types, apartments, list_of_operations)

  elif command[0] == "list":
    process_command_display(command, apartments)

  elif command[0] == "filter":
    apartments, list_of_operations = process_command_filter(command, expense_types, apartments, list_of_operations)

  elif command[0] == "undo":
    apartments, list_of_operations = process_command_undo(command, apartments, list_of_operations)
  
  return apartments, list_of_operations

def print_ui():
  apartments = functions.add_random_values()
  list_of_operations = []
  while True:
    print("Enter a command")
    command = input().split()
    apartments, list_of_operations = process_command(command, apartments, list_of_operations)