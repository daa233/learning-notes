;;; if
(define p 80)

(if (> p 70) 
    'safe
    'unsafe)
;;; safe

(if (< p 90)
    'low-pressure) ; no “else” branch
;;; low-pressure

;;; when
(when (< p 100)
    (display "< 100")
    (newline))

;;; unless
(unless (>= p 100)
    (display "< 100")
    (newline))

;;; cond
(define c #\c)
(cond ((char<? c #\c) -1)
      ((char=? c #\c) 0)
      (else 1))
;Value: 0

;;; case
(case c
    ((#\a) 1)
    ((#\b) 2)
    ((#\c) 3)
    (else 4))
;Value: 3

;;; and
(and 1 2)   ; 2
(and #f 1)  ; #f

;;; or
(or 1 2)    ; 1
(or #f 1)   ; 1

(and 1 #f expression-guaranteed-to-cause-error) ; #f
(or 1 #f expression-guaranteed-to-cause-error)  ; 1
