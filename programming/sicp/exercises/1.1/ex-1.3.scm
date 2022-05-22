;;; Define a procedure that takes three numbers as arguments and returns the 
;;; the sum of the squares of the two larger numbers.
(define (sum-of-two-largest-squares a b c)
    (define (square x) (* x x))
    (define (sum-of-squares x y)
        (+ (square x) (square y)))
    (define (<= a b)
        (if (or (< a b) (= a b))
            a
            b))
    (cond ((and (<= a b) (<= a c)) (sum-of-squares b c))
          ((and (<= b a) (<= b c)) (sum-of-squares a c))
          (else (sum-of-squares a b))))

(sum-of-two-largest-squares 1 2 3)
;; 13
