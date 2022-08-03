;;; Pascal's triangle （也称为“杨辉三角”）
;;;         1
;;;       1   1
;;;     1   2   1
;;;   1   3   3   1
;;; 1   4   6   4   1
;;;        ...
;;; The numbers at the edge of the triangle are all 1, and each number inside
;;; the triangle is the sum of the two numbers above it.
;;; Write a procedure that computes elements of Pascal’s triangle by means of
;;; a recursive process.

(define (pascal-triangle row col)
    (cond ((or (< row col) (< col 1)) 0)
          ((or (= col 1) (= col row)) 1)
          (else (+ (pascal-triangle (- row 1) (- col 1))
                   (pascal-triangle (- row 1) col)))))

; (display (pascal-triangle 1 1)) (newline)   ; 1
; (display (pascal-triangle 2 1)) (newline)   ; 1
; (display (pascal-triangle 2 2)) (newline)   ; 1
; (display (pascal-triangle 3 2)) (newline)   ; 2
; (display (pascal-triangle 5 3)) (newline)   ; 6

(define (print-pascal-triangle row)
    (let row-loop ((i 1) (row row))
        (if (> i row)
            #<void>
            (begin
                (display (make-string (* 2 (- row i)) #\space))
                (let col-loop ((j 1) (col i))
                    (if (> j col)
                        (newline)
                        (begin
                            (display (pascal-triangle i j))
                            (display "   ")
                            (col-loop (+ j 1) col))))
                (row-loop (+ i 1) row)))))

(print-pascal-triangle 5)
