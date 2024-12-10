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

; 1. For a given tree of type (1) return the path from the root node to a certain given node X.

; pargurg_st(l1l2...ln, nrNoduri, nrMuchii) = 
; = nil, if n = 0
; = nil, if nrNoduri = 1 + nrMuchii
; = {l1} U {l2} U parcurg_st(l3...ln, nrNoduri + 1, l2 + nrMuchii), otherwise

(defun left_traversal(l n m)
    (
        cond
        ((null l) nil)
        ((= n (+ 1 m)) nil)
        (t (cons (car l) (cons (cadr l) (left_traversal (cddr l) (+ 1 n) (+ (cadr l) m)))))
    )
)


; (defun parcurg_st (l nrNoduri nrMuchii)
;   (cond
;     ((null l) nil)
;     ((= nrNoduri ( + 1 nrMuchii)) nil)
;     (t (cons (car l) (cons (cadr l) (parcurg_st (cddr l) (+ 1 nrNoduri) (+ (cadr l) nrMuchii)))))
;   )
; )

; pargurg_dr(l1l2...ln, nrNoduri, nrMuchii) =
; = nil, if n = 0
; = nil, if nrNoduri = 1 + nrMuchii
; = {l1} U {l2} U parcurg_dr(l3...ln, nrNoduri + 1, l2 + nrMuchii), otherwise

(defun right_traversal(l n m)
    (
        cond
        ((null l) nil)
        ((= n (+ 1 m)) l)
        (t (right_traversal (cddr l) (+ 1 n) (+ (cadr l) m)))
    )
)

; (defun parcurg_dr (l nrNoduri nrMuchii)
;   (cond
;     ((null l) nil)
;     ((= nrNoduri (+ 1 nrMuchii)) l)
;     (t (parcurg_dr (cddr l) (+ 1 nrNoduri) (+ (cadr l) nrMuchii)))
;   )
; )



;stang(l1l2...ln) = 
; = parcurg_st(l3...ln, 0,0)

(defun left(l)
  (left_traversal (cddr l) 0 0)
)

;drept(l1l2...ln) =
; = parcurg_dr(l3...ln, 0, 0)

(defun right(l)
  (right_traversal (cddr l) 0 0)
)

; checkExistence(l1l2...ln, elem) = 
; = true, if l1 = elem
; = false , if n = 0
; = checkExistence(l2...ln, elem), otherwise

(defun checkExistence(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) t)
    (t (checkExistence (cdr l) elem))
  )
)

(defun checkExistenceLeft(l elem)
  (checkExistence (left l) elem)
)

(defun checkExistenceRight(l elem)
  (checkExistence (right l) elem)
)

; path(l1l2...ln, elem) = 
; = nil, if n = 0
; = list(elem), if elem = l1
; = {l1} U path(drept(l1l2...ln), elem), if checkExistenceRight(l, elem) = true
; = {l1} U path(stang(l1l2...ln), elem), if checkExistenceLeft(l, elem) = true


(defun path(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) (list elem))
    ((checkExistenceRight l elem) (cons (car l) (path (right l) elem)))
    ((checkExistenceLeft l elem) (cons (car l) (path (left l) elem)))
  )
)
(print (path '(A 2 B 0 C 2 D 0 E 0) 'E))