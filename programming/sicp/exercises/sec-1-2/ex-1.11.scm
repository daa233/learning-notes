;;; A function f is defined by the rule that
;;; f(n) = n if n < 3,
;;; f(n) = f(n-1) + 2f(n-2) + 3f(n-3) if n >= 3.

;;; Write a procedure that computes f by means of a recursive process.
(define (f-recursive n)
    (if (< n 3)
        n
        (+ (f-recursive (- n 1))
           (* 2 (f-recursive (- n 2)))
           (* 3 (f-recursive (- n 3))))))


;;; Write a procedure that computes f by means of an iterative process.
(define (f-iterative n)
    (define (f-iter a b c count)
        (if (= count n)
            c
            (f-iter (+ a (* 2 b) (* 3 c))
                    a
                    b
                    (+ count 1))))
    (f-iter 2 1 0 0))


(display (f-recursive 1)) (newline)     ; 1
(display (f-recursive 3)) (newline)     ; 4
(display (f-recursive 10)) (newline)    ; 1892

(display (f-iterative 1)) (newline)     ; 1
(display (f-iterative 3)) (newline)     ; 4
(display (f-iterative 10)) (newline)    ; 1892
