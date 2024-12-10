; a) Write twice the n-th element of a linear list. Example: for (10 20 30 40 50) and n=3 will produce 
; (10 20 30 30 40 50).

(defun twice_nth (lst n)
    (
        cond 
            ((null lst) nil)
            ((= n 1) (cons (car lst) lst))
            (t (cons (car lst) (twice_nth (cdr lst) (- n 1))))
    )   
)

(print (twice_nth '(10 20 30 40 50) 3))

; b) Write a function to return an association list with the two lists given as parameters.
; Example: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).

(defun assoc_list (lst1 lst2)
    (
        cond 
            ((and (null lst1) (null lst2)) nil)
            ((null lst1) (list (cons nil (car lst2))))
            ((null lst2) (list (cons (car lst1) nil)))
            (t (cons (cons (car lst1) (car lst2)) (assoc_list (cdr lst1) (cdr lst2))))
    )   
)

(print (assoc_list '(A B C Q) '(X Y Z T U)))

; c) Write a function to determine the number of all sublists of a given list, on any level.
;  A sublist is either the list itself, or any element that is a list, at any level. Example:
;  (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 lists:
;  (list itself, (3 ...), (4 5), (6 7), (9 10)).

(defun cnt_sublists(l)
    (
        cond
            ((atom l) 0)
            (t (+ 1 (apply '+ (mapcar 'cnt_sublists l))))
    )
)

(print (cnt_sublists '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

; d) Write a function to return the number of all numerical atoms in a list at superficial level.
; (print (countNumbers '(1 2 s 5 (6) fg 5))) => 4

(defun countNumbers(l)
    (
        cond
            ((null l) 0)
            ((numberp (car l)) (+ 1 (countNumbers (cdr l))))
            (t (countNumbers (cdr l)))
    )
)

(print (countNumbers '(1 2 s 5 (6) fg 5)))

