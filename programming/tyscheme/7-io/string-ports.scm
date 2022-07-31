;;; String ports

(define i (open-input-string "hello world"))

(read-char i)   ; #\h

(read i)        ; ello

(read i)        ; world

(define o (open-output-string))

(write 'hello o)
(write-char #\, o)
(display " " o)
(display "world" o)

(get-output-string o)   ; "hello, world"
