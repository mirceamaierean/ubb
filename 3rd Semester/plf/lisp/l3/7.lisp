; using map functions, write a function that substitutes an element e with all elements of a list L1 at all levels
; of a given list L
; ex: (subst l e l1): subst '(1 2 (3 4) 5) 3 '(a b c) => (1 2 (a b c 4) 5)

; use map function to apply a function to all elements of a list
(defun _subst (l e r)
    (cond
        ((numberp l) (if (= l e) r l))
        ((listp l) (mapcar #'(lambda (a) (_subst a e r)) l))
    )
)

(print (_subst '(1 2 (1 2 (3 1) 2)) 1 '(a b c)))
