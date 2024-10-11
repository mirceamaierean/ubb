import timeit
import functools
from random import randint
import termtables as tt


def print_menu():
    '''
    This function prints the menu of our console driven application
    '''
    print("1. Generate a list of n natural numbers")
    print("2. Sort this list using Cocktail Sort")
    print("3. Sort this list using Strand Sort")
    print("4. Display on a table how the algorithms behave during Best Case")
    print("5. Display on a table how the algorithms behave during Worst Case")
    print("6. Display on a table how the algorithms behave during Average Case")
    print("7. Exit the program")


def generate_n_random_numbers(n):
    '''
    This function generate n natural random numbers that are part of the interval [0, 100]
    '''
    list_of_numbers = []

    for i in range(0, n):
        list_of_numbers.append(randint(0, 100))

    return list_of_numbers


def generate_sorted_list(n):
    '''
    This function generate n natural random numbers that are part of the interval [0, 100] and are in increasing order
    '''
    list_of_numbers = generate_n_random_numbers(n)
    list_of_numbers.sort()
    return list_of_numbers


def generate_reverse_sorted_list(n):
    '''
    This function generate n natural random numbers that are part of the interval [0, 100] and are in decreasing order
    '''
    list_of_numbers = generate_sorted_list(n)
    x = list_of_numbers.reverse()
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
    if (step == 0):
        print_step = 0
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
    return sorted_list


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
    if (step == 0):
        print_step = 0
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


def calculate_time_for_table(n, list_of_numbers):
    '''
    This function calculates the required time for each of the operations for sorting
    '''
    copy_of_numbers = list_of_numbers[:]

    time_cocktail_sort = timeit.Timer(
        functools.partial(cocktail_sort, list_of_numbers, n, 0))
    time_strand_sort = timeit.Timer(
        functools.partial(strand_sort, copy_of_numbers, 0))

    return [n, time_cocktail_sort.timeit(1), time_strand_sort.timeit(1)]


def solve():
    '''
    This functions is where the program is executed for the user
    '''
    print_menu()
    list_of_numbers = []
    header = ["Value of n", "Time necessary for Cocktail Sort",
              "Time necessary for Strand Sort"]

    n = 0
    while True:

        option = int(input("Select an option: "))

        if option == 1:
            n = int(input("Choose a value for n: "))
            list_of_numbers = generate_n_random_numbers(n)
            print(list_of_numbers)

        elif option == 2:
            step = int(input("Choose a value for the step, different from 0: "))
            list_of_numbers = cocktail_sort(list_of_numbers, n, step)
            print("After sorting, the sorted list is", list_of_numbers)

        elif option == 3:
            step = int(input("Choose a value for the step, different from 0: "))
            list_of_numbers = strand_sort(list_of_numbers, step)
            print("After sorting, the list is", list_of_numbers)

        elif option == 4:
            print("The best case is when the array is already sorted")
            print("Complexity of Cocktail Sort is O(n)")
            print("Complexity of Strand Sort is O(n)")
            print("The table below shows the required time for each of the algorithms")
            n = 500
            data = []
            for i in range(5):
                list_of_numbers = generate_sorted_list(n)
                data.append(calculate_time_for_table(n, list_of_numbers))
                n = n * 2
            tt.print(
                data,
                header=header,
                padding=(0, 1),
                style=tt.styles.rounded,
                alignment="ccc"
            )

        elif option == 5:
            print("The worst case is when the array is already sorted\nComplexity of Cocktail Sort is O(n^2)\nComplexity of Strand Sort is O(n^2)\nThe table below shows the required time for each of the algorithms")
            n = 500
            data = []
            for i in range(5):
                list_of_numbers = generate_reverse_sorted_list(n)
                data.append(calculate_time_for_table(n, list_of_numbers))
                n = n * 2
            tt.print(
                data,
                header=header,
                padding=(0, 1),
                style=tt.styles.booktabs,
                alignment="ccc"
            )

        elif option == 6:
            print("The average case is when the array is randomly generated")
            print("Complexity of Cocktail Sort is O(n^2)")
            print("Complexity of Strand Sort is O(n^2)")
            print("The table below shows the required time for each of the algorithms")
            n = 500
            data = []
            for i in range(5):
                list_of_numbers = generate_n_random_numbers(n)
                data.append(calculate_time_for_table(n, list_of_numbers))
                n = n * 2
            tt.print(
                data,
                header=header,
                style=tt.styles.thick_thin,
                padding=(0, 1),
                alignment="ccc"
            )

        elif option == 7:
            print("Goodbye!")
            break
        else:
            print("You must choose a value from 1 to 7")


solve()
