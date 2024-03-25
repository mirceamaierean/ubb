; Write recursive Lisp functions for the following problems (optionally, you may use MAP functions):
; A binary tree is memorised in the following way:
; (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) 

; 3. Return the number of levels of a tree of type
; example: (tree-levels '(A 2 B 0 C 2 D 0 E 0)) => 3

(defun skipFirstTree(l)
  (cond
    ((null l) '())
    ((equal (car (cdr l)) 0) (cdr (cdr l)))
    ((equal (car (cdr l)) 1) (skipFirstTree (cdr (cdr l))))
    (T (skipFirstTree (skipFirstTree (cdr (cdr l)))))
  )
)

(defun treeLevels (tree)
  (cond 
    ((null tree) 0)
    ; if the tree has no subtrees, it has only one level
    ((equal (car (cdr tree)) 0) 1)
    ; if the tree has one subtree, it has one more level than the subtree. to access the subtree, we skip the first 2 elements of the list
    ((equal (car (cdr tree)) 1) (+ 1 (treeLevels (cdr (cdr tree)))))
    ; otherwise, the tree has 2 subtrees. the result will be 1 + max(left_subtree + right_subtree). to acces the first subtree, we apply cdr twice, for the right one, we skipFirstTree with cdr cdr
    (T (+ 1 (max (treeLevels (cdr (cdr tree))) (treeLevels (skipFirstTree (cdr (cdr tree)))))))
  )
)

(defun test()
    (assert (equal (treeLevels '(A 2 B 0 C 2 D 0 E 0)) 3))
    (assert (equal (treeLevels '(X 2 Y 1 P 0 Z 1 Q 0)) 3))
    (assert (equal (treeLevels '(M 1 N 2 O 1 Q 0 P 1 R 0)) 4))
)

(test)