from random import randint


def print_menu():
    '''
    This function prints the menu of our console driven application
    '''
    print("1. Generate a list of n natural numbers")
    print("2. Sort this list using Cocktail Sort")
    print("3. Sort this list using Strand Sort")
    print("4. Exit the program")


def generate_n_random_numbers(n):
    '''
    This function generate n natural random numbers that are part of the interval [0, 100]
    '''
    list_of_numbers = []

    for i in range(0, n):
        list_of_numbers.append(randint(0, 100))

    return list_of_numbers


def strand_sort_print_list_after_step(step, list_of_numbers, sorted_list):
    print("Step", step, ":")
    print("The initial list of numbers is", list_of_numbers)
    print("The sorted list is", sorted_list)


def add_elements_to_the_sublist(list_of_numbers):
    '''
    This function is part of strand sort
    The algorithm first moves the first element of a list into a sub-list.
    It then compares the last element in the sub-list to each subsequent element in the original list. 
    Once there is an element in the original list that is greater than the last element in the sub-list, the element is removed from the original list and added to the sub-list.
    This process continues until the last element in the sub-list is compared to the remaining elements in the original list
    '''
    sub_list = [list_of_numbers[0]]
    list_of_numbers.remove(list_of_numbers[0])
    for value in list_of_numbers:
        if value > sub_list[-1]:
            sub_list.append(value)
            list_of_numbers.remove(value)
    return sub_list, list_of_numbers


def merge_lists(list1, list2):
    '''
    This algorithm merges two lists
    Until one of the lists is empty, we compare the first value from each of the set, we take the one that is smaller, we add it to the list that will be returned, and we remove it from the initial list
    After that, we add to the list the values remaining from the list that is not empty
    '''
    result = []
    while list1 and list2:
        if list1[0] < list2[0]:
            result.append(list1.pop(0))
        else:
            result.append(list2.pop(0))
    result.extend(list1 + list2)
    return result


def strand_sort(list_of_numbers, step):
    '''
    This algorithm sorts the elements using strand sort
    For strand sort, we first call add_elements_to_the_sublist, and after that we merge it with the result from the previous steps
    We are checking for each step if we have to display the elements at that certain point
    If the number of steps required to sort the list is smaller than the one provided by the user, we display the list sorted
    '''
    iteration_step = 0
    print_step = 1
    sorted_list = []
    while list_of_numbers:
        sub_list, list_of_numbers = add_elements_to_the_sublist(
            list_of_numbers)
        sorted_list = merge_lists(sorted_list, sub_list)
        iteration_step += 1
        if iteration_step == print_step:
            strand_sort_print_list_after_step(
                iteration_step, list_of_numbers, sorted_list)
            print_step += step
    print("After sorting, the list is", sorted_list)


def cocktail_sort_print_list_after_step(step, list_of_numbers):
    print("Step", step, ":", list_of_numbers)


def cocktail_sort(list_of_numbers, n, step):
    '''
    Cocktail Sort is a variation of Bubble sort. The Bubble sort algorithm always traverses elements from left and moves the largest element to its correct position in the first iteration and second-largest in the second iteration and so on. Cocktail Sort traverses through a given array in both directions alternatively. Cocktail sort does not go through the unnecessary iteration making it efficient for large arrays.

    We are checking for each step if we have to display the elements at that certain point.
    If the number of steps required to sort the list is smaller than the one provided by the user, we display the list sorted
    '''
    iteration_step = 0
    print_step = 1
    swapped_elements = True
    while swapped_elements == True:
        swapped_elements = False
        i = 0
        while (i + 1 < n):
            if (list_of_numbers[i] > list_of_numbers[i + 1]):
                swapped_elements = True
                list_of_numbers[i], list_of_numbers[i +
                                                    1] = list_of_numbers[i + 1], list_of_numbers[i]
                iteration_step += 1
                if (iteration_step == print_step):
                    cocktail_sort_print_list_after_step(
                        iteration_step, list_of_numbers)
                    print_step += step
            i += 1

        while (i > 0):
            if (list_of_numbers[i] < list_of_numbers[i - 1]):
                swapped_elements = True
                list_of_numbers[i], list_of_numbers[i -
                                                    1] = list_of_numbers[i - 1], list_of_numbers[i]
                iteration_step += 1
                if (iteration_step == print_step):
                    cocktail_sort_print_list_after_step(
                        iteration_step, list_of_numbers)
                    print_step += step
            i -= 1

    return list_of_numbers


def solve():
    '''
    This functions is where the program is executed for the user
    '''
    print_menu()
    list_of_numbers = []
    n = 0
    while True:
        option = int(input("Select an option: "))
        if (option == 1):
            n = int(input("Choose a value for n: "))
            list_of_numbers = generate_n_random_numbers(n)
            print(list_of_numbers)
        elif (option == 2):
            step = int(input("Choose a value for the step: "))
            list_of_numbers = cocktail_sort(list_of_numbers, n, step)
            print("After sorting, the sorted list is", list_of_numbers)
        elif (option == 3):
            step = int(input("Choose a value for the step: "))
            strand_sort(list_of_numbers, step)
        elif (option == 4):
            print("Goodbye!")
            break
        else:
            print("You must choose a value from 1 to 4")


solve()
