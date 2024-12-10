; a) Write a function to return the product of two vectors.

(defun dot_product (v1 v2)
    (
        cond 
            ((null v1) 0)
            (T (+ (* (car v1) (car v2)) (dot_product (cdr v1) (cdr v2))))
    )
)

(print (dot_product '(1 2 3) '(4 5 6)))

; b) Write a function to return the depth of a list.

(defun my_max (a b)
    (if (> a b) a b)
)

; depth of a linear list
; mathematical model:
; depth (L) = 1 + depth (L')

(defun list_depth(l d)
    (
        cond
            ((null l) d)
            ((listp (car l)) (my_max (list_depth (car l) (+ d 1)) (list_depth (cdr l) d)))
            (T (list_depth (cdr l) d))
    )
)

(print (list_depth '(6 (2 3 (4) (5) (6 (7)))) 0))

; c) Write a function to sort a linear list without keeping the double values.

(defun insert_in_list(l e)
    (
        cond
            ((null l) (list e))
            ((= (car l) e) l)
            ((< (car l) e) (cons (car l) (insert_in_list (cdr l) e)))
            (T (cons e l))
    )
)

(defun sort_list(l)
    (
        cond
            ((null l) nil)
            (T (insert_in_list (sort_list (cdr l)) (car l)))
    )
)

(print (sort_list '(1 3 5 7 9 2 4 6 8 10 4)))

; d) Write a function to return the intersection of two sets.

(defun set_intersection(l1 l2)
    (
        cond
            ((null l1) nil)
            ((member (car l1) l2) (cons (car l1) (set_intersection (cdr l1) l2)))
            (T (set_intersection (cdr l1) l2))
    )
)

(print (set_intersection '(1 2 3 4 5) '(1 5 6 7 9)))