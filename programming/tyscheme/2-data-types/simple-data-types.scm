;;; Booleans
(boolean? #t)
(boolean? "Hello, World!")

(not #f)
(not #t)
(not "Hello, World!")

;;; Numbers
(number? 42)
(number? #t)
(complex? 2+3i)
(real? 2+3i)
(real? 3.1415926)
(real? 24/7)
(real? 42)
(rational? 2+3i)
(rational? 3.1415926)
(rational? 22/7)
(integer? 22/7)
(integer? 42)

(= #b1100 12)
(= #o14 12)
(= #xc 12)
(= #d12 12)

(eqv? 42 42)
(eqv? 42 #f)    ; #f
(eqv? 42 42.0)  ; #f

(= 42 42)
(= 42 42.0)     ; #t

(< 3 2)
(>= 4.5 3)

(+ 1 2 3)
(- 5.3 2)
(- 5 2 1)
(* 1 2 3)
(/ 6 3)
(/ 22 7)
(expt 2 3)
(expt 4 1/2)

(- 4)   ; -4
(/ 4)   ; 1/4

(max 1 3 4 2 3)
(min 1 3 4 2 3)

(abs 3)
(abs -4)

(round 2.718)       ; 3
(ceiling 2.718)     ; 3
(floor 2.718)       ; 2

;;; Characters
(char? #\c)
(char? 1)
(char? #\;)

(char=? #\a #\a)
(char<? #\a #\b)
(char>=? #\a #\b)

;;; case-insensitive comparisons
(char-ci=? #\a #\A)     ; #t
(char-ci<=? #\a #\B)    ; #t

(char-downcase #\A)     ; #\a
(char-upcase #\a)       ; #\A

;;; Symbols
(quote xyz)

'E

(quote E)

(symbol? 'xyz)
(symbol? 42)

(eqv? 'Calorie 'calorie)

(define xyz 9)
xyz ; 9

(symbol? xyz)   ; #f
(symbol? 'xyz)  ; #t

(set! xyz #\c)
xyz ; #\c
(display (string->symbol "xyz"))
