;;; Exercise 1.10: Ackermann's function

(define (A x y)
    (cond ((= y 0) 0)
          ((= x 0) (* 2 y))
          ((= y 1) 2)
          (else (A (- x 1) (A x (- y 1))))))

(display (A 1 10)) (newline)
;;; (A 0 (A 1 9))
;;; (A 0 (A 0 (A 1 8)))
;;; (A 0 ... (A 0 (A 1 1)))
;;; (A 0 ... (A 0 2))
;;; 2^10

(display (A 2 4)) (newline)
;;; (A 1 (A 2 3))
;;; (A 1 (A 1 (A 2 2)))
;;; (A 1 ... (A 1 (A 2 1)))
;;; (A 1 ... (A 1 2))
;;; (2^(2^(2^2)))
;;; 65536

(display (A 3 3)) (newline)
;;; (A 2 (A 3 2))
;;; (A 2 (A 2 (A 3 1)))
;;; (A 2 (A 2 2))
;;; (A 2 (2^2))
;;; 65536

(define (f n) (A 0 n))
;;; (A 0 n)
;;; (* 2 n)
;;; 2n

(define (g n) (A 1 n))
;;; (A 1 n)
;;; (A 0 (A 1 (- n 1)))
;;; (A 0 (A 0 (A 1 (- n 2))))
;;; 0 for n = 0
;;; 2^n for n > 0

(define (h n) (A 2 n))
;;; 0 for n = 0
;;; 2 for n = 1
;;; 2^(2^(2^...(2^2))) (with the number of 2 is n) for n > 1

(define (k n) (* 5 n n))
;;; 5n^2
