; ; 8.lisp 
; ; a) Write a function to return the difference of two sets.

(defun contains(l e)
    (cond
        ((null l) nil)
        ((= (car l) e) t)
        (t (contains (cdr l) e))
    )
)

(defun difference(l1 l2)
    (cond
        ((null l1) nil)
        ((contains l2 (car l1)) (difference (cdr l1) l2))
        (t (cons (car l1) (difference (cdr l1) l2)))
    )
)

(print (difference '(1 2 3 4 5) '(6 7 8 9)))

; b) Write a function to reverse a list with its all sublists, on all levels.

(defun reverse_list (l)
    (cond
        ((null l) nil)
        ((listp (car l)) (append (reverse_list (cdr l)) (list (reverse_list (car l)))))
        (T (append (reverse_list (cdr l)) (list (car l))))
    )
)

(print (reverse_list '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

; (print (my_reverse '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

; c) Write a function to return the list of the first elements of all list elements of a given list with an odd
; number of elements at superficial level. Example:


(defun odd_length(l)
    (= (mod (length l) 2) 1)
)

(defun first_elem (l)
    (cond
        ((atom l) nil)
        ((odd_length l) (cons (car l) (apply 'append (mapcar 'first_elem (cdr l)))))
        (T (apply 'append (mapcar 'first_elem (cdr l))))
     )
)
(print (first_elem '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

; d) Write a function to return the sum of all numerical atoms in a list at superficial level.

(defun sum_numerical(l)
    (cond
        ((numberp l) l)
        ((atom l) 0)
        ((listp l) (apply '+ (mapcar 'sum_numerical l)))
    )
)

(print (sum_numerical '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))
