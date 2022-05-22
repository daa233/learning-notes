;;; Excercise 1.8: Find cube roots by Newton's method.

(define (<= x y)
    (or (< x y) (= x y)))

(define (cute-root x)
    (define eps 0.0001)

    (define (improve guess)
        (/ (+ (/ x (* guess guess)) (* 2 guess)) 3.0))

    (define (good-enough? guess)
        (<= (abs (- (improve guess) guess)) (* guess eps)))
    
    (define (cute-root-iter guess)
        (if (good-enough? guess)
            guess
            (cute-root-iter (improve guess))))

    (cute-root-iter 1))


(display "(cute-root 8) = ") (display (cute-root 8)) (newline)
(display "(cute-root 27) = ") (display (cute-root 27)) (newline)
(display "(cute-root 0) = ") (display (cute-root 0)) (newline)
