;;; Sequencing
;;; explicit `begin`
(define display3
    (lambda (arg1 arg2 arg3)
        (begin
            (display arg1)
            (display " ")
            (display arg2)
            (display " ")
            (display arg3)
            (newline))))

(display3 "a" "b" "c")  ; a b c

;;; implicit `begin`
(define display3-impl
    (lambda (arg1 arg2 arg3)
        (display arg1)
        (display " ")
        (display arg2)
        (display " ")
        (display arg3)
        (newline)))

(display3-impl "a" "b" "c") ; a b c
