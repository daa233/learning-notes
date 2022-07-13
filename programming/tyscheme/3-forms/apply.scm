;;; Variable number of arguments
(define my-sum
    (lambda args
        (apply + args)))

;;; apply lets us call a procedure on a list of its arguments.
(apply my-sum '(1 2 3 4))   ; 10

(define (my-mul . args)
    (apply * args))

;;; NOTE: The last argument must be a list
(apply my-mul 5 '(1 2 3 4)) ; 120
(my-mul 1 2 3 4)    ; 24
