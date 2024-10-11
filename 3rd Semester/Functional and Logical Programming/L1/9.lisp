; a) Write a function that merges two sorted linear lists and keeps double values.

(defun merge_lists(l1 l2)
    (cond
        ((and (null l1) (null l2)) nil)
        ((null l1) l2)
        ((null l2) l1)
        ((< (car l1) (car l2)) (cons (car l1) (merge_lists (cdr l1) l2)))
        (T (cons (car l2) (merge_lists l1 (cdr l2))))
    )
)

(print (merge_lists '(1 2 3 3) '(3 4 4 5 5 7)))

; b) Write a function to replace an element E by all elements of a list L1 at all levels of a given list L.

(defun replace_element(e l1 l)
    (cond
        ((null l) nil)
        ((atom (car l)) (cond
            ((equal e (car l)) (append l1 (replace_element e l1 (cdr l))))
            (T (cons (car l) (replace_element e l1 (cdr l))))
        ))
        (T (cons (replace_element e l1 (car l)) (replace_element e l1 (cdr l))))
    )
)

(print (replace_element 'a '(1 2 3) '(a (b c) a (a b c) a)))

; c) Write a function to determines the sum of two numbers in list representation, and returns the
; corresponding decimal number, without transforming the representation of the number from list to
; number.

(defun digit (l k c)
    (cond
        ((null l) (mod (+ k c) 10))
        ((null k) (mod (+ l c) 10))
        (T (mod (+ l k c) 10))
    )
)

(defun carry (l k c)
    (cond
        ((null l) (floor (+ k c) 10))
        ((null k) (floor (+ l c) 10))
        (T (floor (+ l k c) 10))
    )
)

(print (carry 9 nil 1))

(defun sum_lists (l k c)
    (cond
        ((and (null l) (null k)) (if (= 1 c) (list 1) nil))
        (T (append (sum_lists (cdr l) (cdr k) (carry (car l) (car k) c)) (list (digit (car l) (car k) c))))        
    )
)

(defun compute_sum(l1 l2)
    (cond
        (t (sum_lists (reverse l1) (reverse l2) 0))
    )
)

(print (compute_sum '(1 2 3) '(9 5 9)))

; d) Write a function to return the greatest common divisor of all numbers in a linear list.

(defun _gcd(a b)
(
    cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((= b 0) a)
        (T (_gcd b (mod a b)))
)
)

(defun gcd_list(l)
    (cond
        ((null l) nil)
        ((null (cdr l)) (car l))
        (T (_gcd (car l) (gcd_list (cdr l))))
    )
)

(print (gcd_list '(24 16 12 A B 72)))
