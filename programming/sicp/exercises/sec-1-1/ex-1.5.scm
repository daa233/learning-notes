;;; Ben Bitdiddle's test code: test whether the interpreter is using
;;; applicative-order evaluation or normal-order evaluation.

(define (p) (p))
(define (test x y)
    (if (= x 0) 0 y))

(test 0 (p))

;; applicative-order evaluation: (dead loop)
;; normal-order evaluation: 0
