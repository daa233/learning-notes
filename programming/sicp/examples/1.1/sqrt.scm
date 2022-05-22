;;; Find square roots by Newton's method

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
        (if (good-enough? guess)
            guess
            (sqrt-iter (improve guess))))
    (sqrt-iter 1))

(display "(sqrt 4) = ") (display (sqrt 4)) (newline)
(display "(sqrt 3) = ") (display (sqrt 3)) (newline)
