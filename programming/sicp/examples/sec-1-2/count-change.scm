;;; How many dif- ferent ways can we make change of $1.00, given half-dollars,
;;; quarters, dimes, nickels, and pennies?

;;; The number of ways to change amount a using n kinds of coins equals
;;;   - the number of ways to change amount a using all but the first kind
;;;     of coin, plus
;;;   - the number of ways to change amount a − d using all n kinds of coins,
;;;     where d is the denomination of the first kind of coin.


(define (count-change amount)
    (cc amount 5))

(define (cc amount kinds-of-coins)
    (cond ((= amount 0) 1)
          ((or (< amount 0) (= kinds-of-coins 0)) 0)
          (else (+ (cc amount (- kinds-of-coins 1))
                   (cc (- amount (first-denomination kinds-of-coins))
                       kinds-of-coins)))))

(define (first-denomination kinds-of-coins)
    (cond ((= kinds-of-coins 1) 1)      ; pennies
          ((= kinds-of-coins 2) 5)      ; nickels
          ((= kinds-of-coins 3) 10)     ; dimes
          ((= kinds-of-coins 4) 25)     ; quarters
          ((= kinds-of-coins 5) 50)))   ; half-dollars

(display (count-change 100)) (newline)
;;; 292

;;; TODO: Iterative implementaion
