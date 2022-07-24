;;; Pseudorandom-number generators
;;; http://web.mit.edu/scheme_v9.2/doc/mit-scheme-ref/Random-Numbers.html
(random 1.0)    ; .5273047071607297
(random 1.0)    ; .1881378458637763
(random 1.0)    ; .09894813585508044
(random 10)     ; 7
(random 10)     ; 2
(random 100)    ; 79
(random 100)    ; 61

;;; Simulate the throwing of a fair, six-headed die:
;;; The outcomes 1, 2, 3, 4, 5, 6 are equally likely.
(define throw-one-die
    (lambda ()
        (let ((result (ceiling (* (random 1.0) 6))))
            result)))

(throw-one-die) ; 2
(throw-one-die) ; 2
(throw-one-die) ; 5
(throw-one-die) ; 3

(define throw-two-dice
    (lambda ()
        (+ (throw-one-die) (throw-one-die))))

(throw-two-dice)    ; 12
(throw-two-dice)    ; 7
(throw-two-dice)    ; 7
(throw-two-dice)    ; 11
