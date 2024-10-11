import functions

def test_modify_expenses_new_entry():
  ap = functions.add_apartment(10, "gas", 25)
  apartments = []
  apartments = functions.modify_expense(apartments, functions.get_apartment_number(ap), functions.get_apartment_expense_type(ap), functions.get_apartment_expense_amount(ap))
  assert (len(apartments) == 1)

  ap = functions.add_apartment(10, "gas", 45)
  apartments = functions.modify_expense(apartments, functions.get_apartment_number(ap), functions.get_apartment_expense_type(ap), functions.get_apartment_expense_amount(ap))
  assert (len(apartments) == 1)

def test_delete_apartment():
  ap1 = functions.add_apartment(10, "gas", 25)
  ap2 = functions.add_apartment(10, "water", 25)
  ap3 = functions.add_apartment(10, "heating", 25)
  ap4 = functions.add_apartment(10, "electricity", 25)
  ap5 = functions.add_apartment(10, "other", 25)
  apartments = [ap1, ap2, ap3, ap4, ap5]
  apartments, list_of_operations = functions.delete_apartments_between_indexes(10, 10, apartments)
  assert (len(apartments) == 0)
  assert (len(list_of_operations) == 5)

def test_delete_apartments_between_indexes():
  ap1 = functions.add_apartment(10, "gas", 25)
  ap2 = functions.add_apartment(20, "water", 25)
  ap3 = functions.add_apartment(30, "heating", 25)
  ap4 = functions.add_apartment(40, "electricity", 25)
  ap5 = functions.add_apartment(50, "other", 25)
  apartments = [ap1, ap2, ap3, ap4, ap5]
  apartments, list_of_operations = functions.delete_apartments_between_indexes(17, 42, apartments)
  assert (len(apartments) == 2)
  assert (len(list_of_operations) == 3)


def test_all():
  test_modify_expenses_new_entry()
  test_delete_apartment()
  test_delete_apartments_between_indexes()