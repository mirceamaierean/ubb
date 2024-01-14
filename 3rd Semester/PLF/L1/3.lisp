; a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.

(defun insert_in_list(l a pos)
    (
        cond
            ((null l) nil)
            ((equal (mod pos 2) 0) (cons (car l) (cons a (insert_in_list (cdr l) a (+ pos 1)))))
            (T (cons (car l) (insert_in_list (cdr l) a (+ pos 1))))
    )
)

(defun solve(l a)
    (insert_in_list l a 1)
)

(print (solve '(1 2 3 4 5 6 7 8) 78))

; b) Write a function to get from a given list the list of all atoms, on any level, but reverse order

(defun reverse_list(l)
    (
        cond
            ((null l) nil)
            (T (append (reverse_list (cdr l)) (list (car l))))
    )
)

(defun get_atoms(l)
    (
        cond
            ((null l) nil)
            ((atom (car l)) (cons (car l) (get_atoms (cdr l))))
            (T (append (get_atoms (car l)) (get_atoms (cdr l))))
    )
)

(defun solve(l)
    (reverse_list (get_atoms l))
)

(print (solve '(1 2 (3 4 (5 6)) 7 8)))

; c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list. 
; the list can contain numbers, strings or other lists.

(defun _gcd(a b)
    (cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((= b 0) a)
        (T (_gcd b (mod a b)))
    )
)

(defun list_gcd(l)
    (
        cond
            ((and (atom (car l)) (null (cdr l))) (car l))
            ((listp (car l)) (_gcd (list_gcd (car l)) (list_gcd (cdr l))))
            (T (_gcd (car l) (list_gcd (cdr l))))
    ))

(print (list_gcd '(24 ( 16 (12 A B)) 72)))

; d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.

(defun occurences(l a)
    (
        cond
            ((null l) 0)
            ((listp (car l)) (+ (occurences (car l) a) (occurences (cdr l) a)))
            ((equal (car l) a) (+ 1 (occurences (cdr l) a)))
            (T (occurences (cdr l) a))
    )
)

(print (occurences '(1 (3 (5 4 3) (5 3)) 3 3) 3))
