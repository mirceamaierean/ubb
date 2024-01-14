; 1
; a) Write a function to return the n-th element of a list, or NIL if such an element does not exist;

(defun nth_element(l n pos)
    (cond 
        ((null l) nil)
        ((= n pos) (car l))
        (t (nth_element (cdr l) n (+ pos 1)))
    )
)

(defun n_elem(l n)
    (nth_element l n 1)
)

(print (n_elem '(1 2 3 4 5 6 7 8 9 10) '5))

; b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.

(defun member_of_list(l e)
    (
        cond
            ((null l) nil)
            ((and (atom (car l)) (equal (car l) e)) t)
            ((atom (car l)) (member_of_list (cdr l) e)) 
            ((list (car l)) (or (member_of_list (car l) e) (member_of_list (cdr l) e)))
    )
)

(print (member_of_list '(1 2 (3 (a 5) (6 7)) 8 (9 10)) 'a))


; c) Write a function to determine the list of all sublists of a given list, on any level.
;  A sublist is either the list itself, or any element that is a list, at any level. Example:
;  (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
;  ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )

(defun all_sublists(l)
    (
        cond
            ((atom l) nil)
            (T (apply 'append (list l) (mapcar 'all_sublists l)))
    )
)

(print (all_sublists '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

; d) Write a function to transform a linear list into a set.

(defun remove_duplicates(l e)
    (
        cond
            ((null l) nil)
            ((equal (car l) e) (remove_duplicates (cdr l) e))
            (T (cons (car l) (remove_duplicates (cdr l) e)))   
    )   
)

(defun transform_set(l)
    (
        cond
            ((null l) nil)
            (T (cons (car l) (transform_set (remove_duplicates (cdr l) (car l)))))
    )
)

(print (transform_set '(1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10)))