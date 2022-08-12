;;; Excercise 1.6: Find square roots by Newton's method with `new-if`

(define (new-if predicate then-clause else-clause)
    (cond (predicate then-clause)
          (else else-clause)))

(define (sqrt x)
    (define eps 0.0001)
    (define (square x) (* x x))
    (define (average x y)
        (/ (+ x y) 2.0))
    (define (improve guess)
        (average guess (/ x guess)))
    (define (good-enough? guess)
        (< (abs (- (square guess) x)) eps))
    (define (sqrt-iter guess)
        (new-if (good-enough? guess)
            guess
            (sqrt-iter (improve guess))))
    (sqrt-iter 1))

(display "(sqrt 4) = ") (display (sqrt 4)) (newline)
;Aborting!: maximum recursion depth exceeded

(display "(sqrt 3) = ") (display (sqrt 3)) (newline)
;Aborting!: maximum recursion depth exceeded

;;; Explaination: The applicative-order evaluation needs evaluate all arguments values,
;;; which is different from `if` expression (only evaluates `<predicate>`).
