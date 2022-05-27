;;; The evaluation allows for combinations whose operators are
;;; compound expressions.

(define (a-plus-abs-b a b)
    ((if (> b 0) + -) a b))

(a-plus-abs-b 1 -2)
;; 3

(a-plus-abs-b 1 2)
;; 3
