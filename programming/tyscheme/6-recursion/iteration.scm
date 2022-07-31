;;; Iteration

;;; Get the index of value o in list l
(define list-position
    (lambda (o l)
        (let loop ((i 0) (l l))
            (if (null? l) #f
                (if (eqv? (car l) o) i
                    (loop (+ i 1) (cdr l)))))))


(define a (list 1 2 3 4))

a   ; (1 2 3 4)

(list-position 3 a) ; 2, the index of value 3 in list a is 2

;;; Reverse the given list s
(define reverse!
    (lambda (s)
        (let loop ((s s) (r '()))
            (if (null? s) r
                (let ((d (cdr s)))
                    (set-cdr! s r)
                        (loop d s))))))

(reverse! a)    ; (4 3 2 1)

(define *num-trials* 10000)

;;; Monte-Carlo method: Find the expected result by repeat the given
;;; experiment number of times.
(define monte-carlo
    (lambda (experiment)
        (let loop ((i 0) (acc 0.0))
            (if (= i *num-trials*)
                (/ acc *num-trials*)
                (loop (+ i 1) (+ acc (experiment)))))))

;;; load procedure 'throw-one-die' and 'throw-two-dice'
(load "../5-lexical-variables/pseudorandom-number-generator.scm")

(monte-carlo throw-one-die)     ; 3.5114
(monte-carlo throw-two-dice)    ; 7.0011
