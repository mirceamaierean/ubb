def add_greater_elements(arr, m, fr, n):
    for i in range(arr[-1] + m, n + 1):
        if fr[i] == 1:
            fr[i] = 0
            arr.append(i)
            recursive_backtracking(arr, m, fr, n)
            arr.pop()
            fr[i] = 1


def add_smaller_elements(arr, m, fr, n):
    for i in range(arr[-1] - m, 0, -1):
        if fr[i] == 1:
            fr[i] = 0
            arr.append(i)
            recursive_backtracking(arr, m, fr, n)
            arr.pop()
            fr[i] = 1


def recursive_backtracking(arr, m, fr, n):
    if len(arr) == n:
        print(arr)
        return

    add_greater_elements(arr, m, fr, n)
    add_smaller_elements(arr, m, fr, n)


def solve_using_iterative_backtracking(n, m):
    for el in range(1, n + 1):
        if el >= n - m and n / 2 != m:
            fr = [0] * (n + 1)
            arr = [el]
            fr[el] = 1
            last_deleted_element = -1
            while len(arr) > 0:
                if len(arr) == n:
                    print(arr)
                else:
                    if last_deleted_element == -1:
                        added_element = False
                        for i in range(arr[-1] + m, n + 1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == False:
                            for i in range(arr[-1] - m, 0, -1):
                                if fr[i] == 0:
                                    fr[i] = 1
                                    arr.append(i)
                                    last_deleted_element = -1
                                    added_element = True
                                    break
                        if added_element == True:
                            continue
                    elif last_deleted_element > arr[-1]:
                        added_element = False
                        for i in range(last_deleted_element + 1, n + 1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == True:
                            continue
                    elif last_deleted_element < arr[-1]:
                        added_element = False
                        for i in range(last_deleted_element - 1, 0, -1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == True:
                            continue
                last_deleted_element = arr[-1]
                fr[last_deleted_element] = 0
                arr.pop()
        if el <= m + 1:
            fr = [0] * (n + 1)
            arr = [el]
            fr[el] = 1
            last_deleted_element = -1
            while len(arr) > 0:
                if len(arr) == n:
                    print(arr)
                else:
                    if last_deleted_element == -1:
                        added_element = False
                        for i in range(arr[-1] - m, 0, -1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == False:
                            for i in range(arr[-1] + m, n + 1):
                                if fr[i] == 0:
                                    fr[i] = 1
                                    arr.append(i)
                                    last_deleted_element = -1
                                    added_element = True
                                    break
                        if added_element == True:
                            continue
                    elif last_deleted_element > arr[-1]:
                        added_element = False
                        for i in range(last_deleted_element + 1, n + 1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == True:
                            continue
                    elif last_deleted_element < arr[-1]:
                        added_element = False
                        for i in range(last_deleted_element - 1, 0, -1):
                            if fr[i] == 0:
                                fr[i] = 1
                                arr.append(i)
                                last_deleted_element = -1
                                added_element = True
                                break
                        if added_element == True:
                            continue
                last_deleted_element = arr[-1]
                fr[last_deleted_element] = 0
                arr.pop()


def solve():
    n = int(input("Choose a value for n: "))
    m = int(input("Choose a value for m: "))

    if (m > n // 2):
        print("An array that satisfies the requirements does not exist")
        return

    print("Using recursive backtracking, the generated arrays are")
    solve_using_recursive_backtracking(n, m)
    print("Using iterative backtracking, the generated arrays are")
    solve_using_iterative_backtracking(n, m)


def solve_using_recursive_backtracking(n, m):
    fr = [1] * (n + 1)
    for i in range(1, n + 1):
        fr[i] = 0
        arr = [i]
        recursive_backtracking(arr, m, fr, n)
        fr[i] = 1


solve()
