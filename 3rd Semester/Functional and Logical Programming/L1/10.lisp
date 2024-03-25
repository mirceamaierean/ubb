; a) Write a function to return the product of all the numerical atoms from a list, at superficial level.

(defun prod(l p)
    (cond
        ((null l) p)
        ((numberp (car l)) (prod (cdr l) (* p (car l))))
        (t (prod (cdr l) p))
    )
)

(defun find_prod(l)
    (prod l 1)
)

(print (find_prod '(1 A 2 3 (3 4 5) T)))

; b) Write a function to replace the first occurence of an element E in a given list with an other element O.

(defun replace_occurence(l e o)
    (cond
        ((null l) nil)
        ((listp (car l)) (cons (replace_occurence (car l) e o) (replace_occurence (cdr l) e o)))
        ((equal (car l) e) (cons o (cdr l)))
        (t (cons (car l) (replace_occurence (cdr l) e o))
    )
    )
)

(print (replace_occurence '(1 2 3 4 5) 3 6))

; c) Write a function to compute the result of an arithmetic expression memorised
;  in preorder on a stack. Examples:
;  (+ 1 3) ==> 4 (1 + 3)
;  (+ * 2 4 3) ==> 11 [((2 * 4) + 3)
;  (+ * 2 4 - 5 * 2 2) ==> 9 ((2 * 4) + (5 - (2 * 2))

(defun _expression (op a b)
	(cond
		((string= op "+") (+ a b))
		((string= op "-") (- a b))
		((string= op "*") (* a b))
		((string= op "/") (floor a b))
	)
)

(defun expression (l)
    (cond
        ((null l) nil)
        ((and (and (numberp (cadr l)) (numberp (caddr l))) (atom (car l))) (cons (_expression (car l) (cadr l) (caddr l)) (expression (cdddr l))))
        (T (cons (car l) (expression (cdr l))))
    )
)

(defun solve (l)
    (cond
        ((null (cdr l)) (car l))
        (T (solve (expression l)))
    )
)

(print (solve '(+ * 2 4 - 5 * 2 2)))


; d) Write a function to produce the list of pairs (atom n), where atom appears for n times in the
; parameter list. Example:
; (a b a a c c c) ==> ((a 3) (b 1) (c 3))

(defun count_occurence (l e)
    (cond
        ((null l) 0)
        ((equal (car l) e) (+ 1 (count_occurence (cdr l) e)))
        (T (count_occurence (cdr l) e))
    )
)

(defun remove_duplicates (l e)
    (cond
        ((null l) nil)
        ((equal (car l) e) (remove_duplicates (cdr l) e))
        (T (cons (car l) (remove_duplicates (cdr l) e)))
    )
)

(defun count_all_occurences (l)
    (cond
        ((null l) nil)
        (T (cons (cons (car l) (count_occurence l (car l))) (count_all_occurences (remove_duplicates l (car l)))))
    )
)

(print (count_all_occurences '(a b a a c c c)))