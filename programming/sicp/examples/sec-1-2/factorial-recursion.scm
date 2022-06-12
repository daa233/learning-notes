;;; Define factorial function with linear recursion and iteration.

(define (factorial n)
    (if (= n 1)
        1
        (* n (factorial (- n 1)))))

(display (factorial 5)) (newline)
