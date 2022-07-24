;;; Lexical variables
(define x 9)

(define add2 (lambda (x) (+ x 2)))

x           ; 9

(add2 3)    ; 5
(add2 x)    ; 11

x           ; 9

(set! x 20)

x           ; 20

(define add2
    (lambda (x)
        (set! x (+ x 2))    ; it shadows the global x
        x))

(add2 x)    ; 22
x           ; 20

(define counter 0)

(define bump-counter
    (lambda ()
        ;; here use global variable counter
        (set! counter (+ counter 1))
        counter))

(bump-counter)  ; 1
(bump-counter)  ; 2
(bump-counter)  ; 3

counter ; 3

;;; let and let*

;;; NOTE: The local variable initializations — x to 1; y to 2; z to 3
;;; — are not considered part of the let body. 
(let ((x 1)
      (y 2)
      (z 3))
    (list x y z))
;;; (1 2 3)

;;; Therefore, a reference to x in the initialization will refer to the global, not the local x
(let ((x 1)
      (y x))    ; y bound to the global x (value 20)
    (+ x y))
;;; 21
 
(let* ((x 1)
       (y x))   ; y bound to the initialization x which the value is 1
    (+ x y))
;;; 2

;;; equivalent to the above let*
(let ((x 1))
    (let ((y x))
        (+ x y)))
;;; 2

;;; The values bound to lexical variables can be procedures
(let ((cons (lambda (x y) (+ x y))))
    (cons 1 2))
;;; 3

;;; fluid-let
;;; use fluid-let to temporarily set a variable to a certain value
(fluid-let ((counter 99))
    (display (bump-counter)) (newline)
    (display (bump-counter)) (newline)
    (display (bump-counter)) (newline))
;;; 100
;;; 101
;;; 102

counter ; 3

(let ((counter 99))
    (display (bump-counter)) (newline)
    (display (bump-counter)) (newline)
    (display (bump-counter)) (newline))
;;; 4
;;; 5
;;; 6

counter ; 6
