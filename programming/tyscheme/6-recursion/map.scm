;;; Mapping a procedure across a list

;;; load procedure 'add2'
(load "../3-forms/procedures.scm")

;;; the map procedure applies a given procedure to every element
;;; of a given list, and returns the list of the results.
(map add2 '(1 2 3)) ; (3 4 5)

;;; the for‑each procedure also applies a procedure to each element
;;; in a list, but returns void. 
(for-each display
    (list "one" "two" "buckle my shoe"))


;;; given an n-argument procedure, map takes n lists and applies the
;;; procedure to every set of n of arguments selected from across the lists
(map cons '(1 2 3) '(10 20 30))
;;; ((1 . 10) (2 . 20) (3 . 30))

(map + '(1 2 3) '(10 20 30))
;;; 11 22 33

