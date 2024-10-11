; a) Write a function to return the sum of two vectors.

(defun sum_vector(v1 v2)
    (
        cond
            ((null v1) nil)
            (T (cons (+ (car v1) (car v2)) (sum_vector (cdr v1) (cdr v2))))
    )
)

(print (sum_vector '(1 2 3) '(4 5 6)))

; b) Write a function to get from a given list the list of all atoms, on any
;  level, but on the same order. Example:
;  (((A B) C) (D E)) ==> (A B C D E)


; cons keeps the same data structure, append just add the elements to the list
(defun get_atoms(l)
(
    cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (get_atoms (cdr l))))
        (T (append (get_atoms (car l)) (get_atoms (cdr l))))
))

(print (get_atoms '(((A B) C) (D E))))

; c) Write a function that, with a list given as parameter, inverts only continuous
;  sequences of atoms. Example:
;  (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))


(defun reverse_list(l)
(
    cond
        ((null l) nil)
        (T (append (reverse_list (cdr l)) (list (car l))))
))

(defun invert_list(l aux)
(
    cond
        ((null l) (reverse_list aux))
        ((listp (car l)) (append (reverse_list aux) (cons (invert_list (car l) nil) (invert_list (cdr l) nil))))
        (T (invert_list (cdr l) (append aux (list (car l)))))
))

(print (invert_list '(a b c (d (e f) g h i)) nil))

; d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level.
;  Example: (a 1 b 2 c 3) ==> 3

(defun my_max (a b)
    (cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((> a b) a)
        (T b)
))

(defun max_list(l)
(
    cond
        ((null (cdr l)) (car l))
        (T (my_max (car l) (max_list (cdr l))))
))

(print (max_list '(A 1 B 4 5 3 C F)))