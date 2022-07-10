;;; Strings
"Hello, World!"

;;; takes a bunch of characters and returns the string made from them
(string #\h #\e #\l #\l #\o)

(define greeting "Hello; Hello;")

;;; individually access and modify, 0-based index
(string-ref greeting 0)             ;; #\H
;;; (string-set! greeting 1 #\a)    ;; error!

;;; create by appending other strings
(string-append "E " "Pluribus " "Unum")

;;; make a string of a specified length and fill it with desired characters
(define a-3-char-long-string (make-string 3))

(display a-3-char-long-string)  ; ""

;;; check stringness
(string? a-3-char-long-string)

(string-set! a-3-char-long-string 0 #\a)
(string-set! a-3-char-long-string 1 #\b)
(string-set! a-3-char-long-string 2 #\c)
(display a-3-char-long-string)  ; "abc"


;;; Vectors
(vector 0 1 2 3 4)  ; #(0 1 2 3 4)

(define v (make-vector 5))
v   ; #(#f #f #f #f #f)

(vector-ref v 0)  ; #f
(vector-set! v 0 -1)
v   ; #(-1 #f #f #f #f)

;;; Dotted pairs and lists
(cons 1 #t) ; (1 . #t)

'(1 . #t)

; (1 . #t)  ; --> ERROR!

(define x (cons 1 #t))

(car x) ; 1

(cdr x) ; #t

(set-car! x 2)
(set-cdr! x #f)
x   ; (2 . #f)

(define y (cons (cons 1 2) 3))
y   ; ((1 . 2) . 3)

(car (car y))   ; 1

(cdr (car y))   ; 2

(caar y)    ; 1

(cdar y)    ; 2

(cons 1 (cons 2 (cons 3 (cons 4 5)))) ; (1 2 3 4 . 5)

'(1 . (2 . (3 . (4 . 5))))  ; (1 2 3 4 . 5)

'() ; (), empty list

'(1 . ( 2 . (3 . (4 . ()))))    ; (1 2 3 4)

(cons 1 (cons 2 (cons 3 (cons 4 '())))) ; (1 2 3 4)

;;; list
(list 1 2 3 4)  ; (1 2 3 4)

'(1 2 3 4)  ; (1 2 3 4)

(define y (list 1 2 3 4))

(list-ref y 0)  ; 1
(list-ref y 3)  ; 4

;;; list‑tail returns the tail of the list starting from the given index
(list-tail y 1) ; (2 3 4)
(list-tail y 3) ; (4)

(pair? '(1 . 2))    ; => #t
(pair? '(1 2))      ; => #t
(pair? '())         ; => #f
(list? '())         ; => #t
(null? '())         ; => #t
(list? '(1 2))      ; => #t
(list? '(1 . 2))    ; => #f
(null? '(1 2))      ; => #f
(null? '(1 . 2))    ; => #f

;;; Conversions between data types
(char->integer #\d) ; => 100
(integer->char 50)  ; => #\2
(string->list "hello")  ; (#\h #\e #\l #\l #\o)
(number->string 16)     ; "16"
(string->number "16")   ; 16
(string->number "Am I a hot number?")   ; #f
(string->number "16" 8) ; 14
(symbol->string 'symbol)    ; "symbol"
(string->symbol "string")   ; symbol
