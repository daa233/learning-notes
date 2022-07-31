;;; Mutually recursive procedures
(define is-even?
    (lambda (n)
        (if (= n 0) #t
            (is-odd? (- n 1)))))

(define is-odd?
    (lambda (n)
        (if (= n 0) #f
            (is-even? (- n 1)))))

(is-even? 2)    ; #t
(is-odd? 2)     ; #f

;;; letrec example: use procedures as local variables
(letrec ((local-even? (lambda (n)
                        (if (= n 0) #t
                            (local-odd? (- n 1)))))
        (local-odd? (lambda (n)
                        (if (= n 0) #f
                            (local-even? (- n 1))))))
    (list (local-even? 23) (local-odd? 23)))
;;; (#f #t)

;;; using letrec describe loops
(letrec ((countdown (lambda (i)
                        (if (= i 0) 'liftoff
                            (begin
                                (display i)
                                (newline)
                                (countdown (- i 1)))))))
    (countdown 10))

;;; using named let to describe loops
(let countdown ((i 10))
    (if (= i 0) 'liftoff
        (begin
            (display i)
            (newline)
            (countdown (- i 1)))))

