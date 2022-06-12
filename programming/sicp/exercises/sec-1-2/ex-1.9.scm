;;; Exercise 1.9: Custom adding two positive integers, iterative vs. recursive.

(define (inc x)
    (+ x 1))


(define (dec x)
    (- x 1))


(define (recursive-plus a b)
    (if (= a 0) b (inc (recursive-plus (dec a) b))))


(define (iterative-plus a b)
    (if (= a 0) b (iterative-plus (dec a) (inc b))))


(display (recursive-plus 4 5)) (newline)
(display (iterative-plus 4 5)) (newline)
