;;; Excercise 1.7: Find square roots by Newton's method with alternative
;;; strategy of `good-enough?`:
;;; Watch how `guess` changes from iteration to the next and to stop when
;;; the change is a very samll fraction of the guess.

(define (<= x y)
    (or (< x y) (= x y)))

(define (sqrt x)
    (define eps 0.0001)
    (define (average x y)
        (/ (+ x y) 2.0))
    (define (improve guess)
        (average guess (/ x guess)))

    (define (good-enough? guess)
        (<= (abs (- (improve guess) guess)) (* guess eps)))
    
    (define (sqrt-iter guess)
        (if (good-enough? guess)
            guess
            (sqrt-iter (improve guess))))

    (sqrt-iter 1))

(display "(sqrt 4) = ") (display (sqrt 4)) (newline)
(display "(sqrt 3) = ") (display (sqrt 3)) (newline)


(define (sqrt-2 x)
    (define eps 0.0001)
    (define (average x y)
        (/ (+ x y) 2.0))
    (define (improve guess)
        (average guess (/ x guess)))

    (define (good-enough? guess old-guess)
        (<= (abs (- guess old-guess)) (* guess eps)))
    
    (define (sqrt-iter guess old-guess)
        (if (good-enough? guess old-guess)
            guess
            (sqrt-iter (improve guess) guess)))

    (sqrt-iter 1 2))

(display "(sqrt 4) = ") (display (sqrt-2 4)) (newline)
(display "(sqrt 3) = ") (display (sqrt-2 3)) (newline)
(display "(sqrt 0) = ") (display (sqrt-2 0)) (newline)
