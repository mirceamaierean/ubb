; a) Write a function to test whether a list is linear.

(defun is_linear(lst)
    (cond
        ((null lst) t)
        ((listp (car lst)) nil)
        (t (is_linear (cdr lst)))
    )
)

(print (is_linear '(1 2 3 4 5)))
(print (is_linear '(1 2 3 (4 5))))

; b) Write a function to replace the first occurence of an element E in a given list with an other element O.

(defun replace_first_occurence(lst e o)
    (cond
        ((null lst) nil)
        ((equal (car lst) e) (cons o (cdr lst)))
        (t (cons (car lst) (replace_first_occurence (cdr lst) e 0)))
    )
)

(print (replace_first_occurence '(1 2 3 3 5) 3 0))

; c) Write a function to replace each sublist of a list with its last element.
;  A sublist is an element from the first level, which is a list.
;  Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
;  (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)

(defun last_element (l)
	(if (listp l) 
        (last_element (car (reverse l)))
        l
    )
)

(defun replace_sublist_with_last_element (l)
    (cond
        ((null l) nil)
        ((listp (car l)) (cons (last_element (car l)) (replace_sublist_with_last_element (cdr l))))
        (t (cons (car l) (replace_sublist_with_last_element (cdr l))))
    )
)

(print (replace_sublist_with_last_element '(a (b c) (d (e (f))))))

; d) Write a function to merge two sorted lists without keeping double values

(defun merge_sorted_lists (l1 l2)
    (cond
        ((null l1) l2)
        ((null l2) l1)
        ((< (car l1) (car l2)) (cons (car l1) (merge_sorted_lists (cdr l1) l2)))
        ((> (car l1) (car l2)) (cons (car l2) (merge_sorted_lists l1 (cdr l2))))
        (t (cons (car l1) (merge_sorted_lists (cdr l1) (cdr l2))))
    )
)

(print (merge_sorted_lists '(1 2 3 4 5) '(2 3 4 5 6)))