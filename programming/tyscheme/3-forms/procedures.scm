;;; Procedures
(lambda (x) (+ x 2))    ; #[compound-procedure 12]

((lambda (x) (+ x 2)) 5)    ; 7

;;; Use a variable to hold the procedure value
(define add2
    (lambda (x) (+ x 2)))

(add2 5)    ; 7

(define area
    (lambda (length breadth)
        (* length breadth)))

(area 4 5)
