#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import random


def add_apartment(apartment, expense_type, amount):
  '''
  apartment: positive integer, represents the apartment number
  expense_type: string, represents the expense of the apartment
  amount: positive integer, represents the amount for that expense
  '''
  return {"apartment": apartment, "type": expense_type, "amount": amount}

def generate_random_apartment():
    expense_type = ["gas", "water", "heating", "electricity", "other"]
    return {"apartment": random.randint(1, 100), "type": expense_type[random.randint(0, 4)], "amount": random.randint(1, 100)}

def get_apartment_number(apartment):
  return apartment['apartment']

def get_apartment_expense_type(apartment):
  return apartment['type']

def get_apartment_expense_amount(apartment):
  return apartment['amount']

def set_value_expense(apartment, amount):
  apartment['amount'] += amount
  return apartment

# ADD Commands
def modify_expense(apartments, apartment, expense_type, amount):
  '''
  apartments: list of apartments
  apartment: positive integer, represents the apartment number
  expense_type: string, represents the expense of the apartment
  amount: positive integer, represents the amount for that expense
  '''
  ok = False
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_type = get_apartment_expense_type(ap)
    if ap_num == apartment and ap_type == expense_type:
      ap = set_value_expense(ap, amount)
      ok = True
  if ok == False:
    apartments.append(add_apartment(apartment, expense_type, amount))
  return apartments

# Remove
def delete_apartments_between_indexes(first_apartment, last_apartment, apartments):
  '''
  apartments: list of apartments
  first_apartment: positive integer, the first apartament from which we iterate
  last_apartment: positive integer, the last apartament to which we iterate
  '''
  new_appartments = []
  restore_op = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_exp_type = get_apartment_expense_type(ap)
    ap_amount = get_apartment_expense_amount(ap)
    if first_apartment > ap_num or ap_num > last_apartment:
      new_appartments.append(ap)
    else:
      operation = "add " + str(ap_num) + " " + ap_exp_type + " " + str(ap_amount)
      restore_op.append(operation)
  return new_appartments, restore_op

def delete_apartments_with_expense_type(expense_type, apartments):
  '''
  expense_type: string, representing the type of the expense
  apartments: list of apartments
  '''
  new_appartments = []
  restore_op = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_exp_type = get_apartment_expense_type(ap)
    ap_amount = get_apartment_expense_amount(ap)
    if ap_exp_type != expense_type:
      new_appartments.append(ap)
    else:
      operation = "add " + str(ap_num) + " " + ap_exp_type + " " + str(ap_amount)
      restore_op.append(operation)
  return new_appartments, restore_op

# Replace
def replace_amounf_of_expense_for_ap(apartments, apartment, expense_type, amount):
  '''
  apartments: list of apartments
  apartment: positive integer, represents the apartment number
  expense_type: string, represents the expense of the apartment
  amount: positive integer, represents the amount for that expense
  '''
  new_ap = []
  restore_op = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_exp_type = get_apartment_expense_type(ap)
    ap_amount = get_apartment_expense_amount(ap)
    if ap_num == apartment and ap_exp_type == expense_type:
      ap = set_value_expense(ap, amount)
      operation = "replace " + str(ap_num) + " " + ap_exp_type + " with " + str(ap_amount)
      restore_op.append(operation)
    new_ap.append(ap)
  return new_ap, restore_op

# Display
def compare_based_on_condition(index, expense_amount, amount):
  ''''
  index: integer, used to determine the sign of the comparison (0 =, 1 <, 1 >)
  '''
  if index == 0:
    return expense_amount == amount
  if index == 1:
    return expense_amount < amount
  return expense_amount > amount

def find_apartments_that_satisfy_the_condition(apartments, amount, index):
  '''
  apartments: list of apartments
  amount: positive integer, represents the amount for that expense
  index: integer, used to determine the sign of the comparison (0 =, 1 <, 1 >)
  '''
  good_apartments = []
  for ap in apartments:
    ap_expense_amount = get_apartment_expense_amount(ap)
    if compare_based_on_condition(index, ap_expense_amount, amount):
      good_apartments.append(ap)
  return good_apartments

def all_expenses_of_apartment(apartments, apartment):
  '''
  apartments: list of apartments
  apartment: positive integer, represents the apartment number
  '''
  good_apartments = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    if ap_num == apartment:
      good_apartments.append(ap)
  return good_apartments

# Filter
def filter_apartment_by_type(apartments, expense_type):
  '''
  apartments: list of apartments
  expense_type: string, represents the expense of the apartment
  '''
  good_apartments = []
  restore_op = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_expense_type = get_apartment_expense_type(ap)   
    ap_amount = get_apartment_expense_amount(ap)
    if ap_expense_type == expense_type:
      good_apartments.append(ap)
    else:
      operation = "add " + str(ap_num) + " " + ap_expense_type + " " + str(ap_amount)
      restore_op.append(operation)
  return good_apartments, restore_op

def filter_apartment_by_amount(apartments, amount):
  '''
  apartments: list of apartments
  amount: positive integer, represents the amount for that expense
  '''
  good_apartments = []
  restore_op = []
  for ap in apartments:
    ap_num = get_apartment_number(ap)
    ap_expense_type = get_apartment_expense_type(ap)   
    ap_amount = get_apartment_expense_amount(ap)
    if ap_amount < amount:
      good_apartments.append(ap)
    else:
      operation = "add " + str(ap_num) + " " + ap_expense_type + " " + str(ap_amount)
      restore_op.append(operation)
  return good_apartments, restore_op

# Undo

def undo_operations(operations, apartments):
  '''
  operation: list of strings, representing the operations we have to do in order to undo the ones we performed before
  apartments: list of apartments 
  '''
  new_op = []
  for op in operations:
    op = op.split()
    ap = add_apartment(int(op[1]), op[2], int(op[3]))
    if (op[0] == "add"):
      apartments = modify_expense(apartments, int(op[1]), op[2], int(op[3]))
    else:
      apartments, new_op = replace_amounf_of_expense_for_ap(apartments, ap, op[2], int(op[3]))
  return apartments

def add_random_values():
  apartments = []
  for i in range(10):
    apartments.append(generate_random_apartment())
  return apartments