;;; Factorial
(define factorial
    (lambda (n)
    (if (= n 0) 1
        (* n (factorial (- n 1))))))

(factorial 0)   ; 1
(factorial 1)   ; 1
(factorial 3)   ; 6
(factorial 5)   ; 120
