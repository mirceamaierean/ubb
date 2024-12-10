; define a function that computes the difference of 2 numbers represented as a list
; example diff((3 3 3)(1 1 1)) = (2 2 2)
; example diff((3 3 3 0)(1 1 1)) = (3 2 1 9)

; define a function to transform the list in a number
(defun transform_in_number(l)
    (
        cond
            ((null l) 0)
            (t (+ (* 10 (transform_in_number (cdr l))) (car l)))
    )
)

(defun reverse_list(l)
    (
        cond
            ((null l) nil)
            (t (append (reverse_list (cdr l)) (list (car l))))
    )
)    

(defun compute_difference(l1 l2)
    (
        cond
        (t (- (transform_in_number (reverse_list l1)) (transform_in_number (reverse_list l2))))
    )
)

(
    defun transform_number_in_list(n)
    (
        cond
            ((= n 0) nil)
            (t (append (transform_number_in_list (floor (/ n 10))) (list (mod n 10))))
            
    )
)

(defun solve(l1 l2)
    (
        transform_number_in_list (compute_difference l1 l2)
    )
)

(defun test()
    (assert (equal (solve '(3 3 3) '(1 1 1)) '(2 2 2)))
    (assert (equal (solve '(3 3 3) '(2 2)) '(3 1 1)))
    (assert (equal (solve '(3 3 3) '(2 8)) '(3 0 5)))
    (assert (equal (solve '(1 1 1) '(2 5)) '(8 6)))
)

(test)