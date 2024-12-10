; Write recursive Lisp functions for the following problems (optionally, you may use MAP functions):
; A binary tree is memorised in the following two ways:
; (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
; (node (list-subtree-1) (list-subtree-2) ...) (2)
; As an example, the tree
;     A
;    / \
;   B   C
;      / \
;     D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)
; (A (B) (C (D) (E))) (2)

; 4. Convert a tree of type (2) to type (1).

(defun convert_tree(l)
    (cond
         ((null l) nil)
         ((and (not (null (cadr l))) (not (null (caddr l)))) (append (list (car l)) '(2) (convert_tree(cadr l))
                                                                     (convert_tree(caddr l))))
         ((not (null (cadr l))) (append (list (car l)) '(1) (convert_tree(cadr l)) ))
         ((not (null (caddr l))) (append (list (car l)) '(1) (convert_tree(caddr l)) ))
         (T (append (list (car l)) '(0)))
    )
)

(print (convert_tree '(A (B) (C (D) (E)))))
