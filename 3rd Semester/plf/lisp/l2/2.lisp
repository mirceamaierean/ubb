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

; 2. Return the list of nodes on the k-th level of a tree of type (1).

; 2. Return the list of nodes on the k-th level of a tree of type (1).


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


(defun nodes(l counter level)
  (cond
    ((null l) nil)
    ((equal counter level) (list (car l)))
    (t (append (nodes (left l) (+ 1 counter) level) (nodes (right l) (+ 1 counter) level)))
  )
)

(defun main(l level)
  (nodes l 0 level)
)

(print (main '(A 2 B 0 C 2 D 0 E 0) 2))