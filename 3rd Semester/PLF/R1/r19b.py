def replace(l, valueToBeReplaced, value):
    if len(l) == 0:
        return l
    if l[0] == valueToBeReplaced:
        return [value] + replace(l[1:], valueToBeReplaced, value)
    return [l[0]] + replace(l[1:], valueToBeReplaced, value)


l = [1, 2, 3, 4, 5, 5, 5, 8, 9]

print(replace(l, 5, 6))
