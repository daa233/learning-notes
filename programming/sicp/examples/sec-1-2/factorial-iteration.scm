;;; Define factorial function with linear recursion and iteration.

(define (factorial n)
    (define (fact-iter i prod)
        (if (= i n)
            prod
            (fact-iter (+ i 1) (* prod (+ i 1)))))
    (fact-iter 1 1))

(display (factorial 5)) (newline)
