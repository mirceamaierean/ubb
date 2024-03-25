; ; a) Write a function to eliminate the n-th element of a linear list.

(defun eliminate(l n)
    (
        cond
        ((null l) nil)
        ((= n 1) (cdr l))
        (t (cons (car l) (eliminate (cdr l) (- n 1))))
    )
)

(print (eliminate '(a b c d e f g) 10))

; b) Write a function to determine the successor of a number represented digit by digit as a list, without
; transforming the representation of the number from list to number. 
; Example: (1 9 3 5 9 9) --> (1 9 3 6 0 0)
; (9 9) --> (1 0 0)

(defun succ(l carry)
    (
        cond
        ((null l) (if (= carry 0) nil (cons carry nil)))
        ((= (car l) 9) (cons 0 (succ (cdr l) 1)))
        (t (cons (+ (car l) carry) (cdr l)))
    )
)

(defun find_next(l)
    (
    cond
        (t (reverse(succ (reverse l) 0)))
    )
)


(print (find_next '(1 9 3 5 9 9)))
(print (find_next '(9 9)))

; c) Write a function to return the set of all the atoms of a list.
;  Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4)) ==> (1 2 3 4)


(defun remove_duplicates(l)
    (
        cond
        ((null l) nil)
        ((member (car l) (cdr l)) (remove_duplicates (cdr l)))
        (t (cons (car l) (remove_duplicates (cdr l))))
    )
)

(defun get_atoms(l)
    (
        cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (get_atoms (cdr l))))
        (t (append (get_atoms (car l)) (get_atoms (cdr l))))
    )
)

(defun get_set(l)
    (
        remove_duplicates (get_atoms l)
    )
)

(print (get_set '(1 (2 (1 3 (2 4) 3) 1) (1 4))))

; d) Write a function to test whether a linear list is a set.

(defun is_set(l)
    (
        cond
        ((null l) t)
        ((member (car l) (cdr l)) nil)
        (t (is_set (cdr l)))
    )
)

(print (is_set '(1 2 3 4)))
(print (is_set '(1 2 3 4 1)))