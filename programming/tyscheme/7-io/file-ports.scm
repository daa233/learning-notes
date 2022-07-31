;;; File ports

;;; the following two lines has the same behavior
(display 9)
(display 9 (current-output-port))

(define i (open-input-file "hello.txt"))

(read-char i)   ; #\h

(define j (read i))
j               ; ello

(close-input-port i)

(define o (open-output-file "greeting.txt"))

(display "hello" o)
(write-char #\space o)
(display 'world o)
(newline o)

(close-output-port o)

;;; automatic opening and closing of file ports
(call-with-input-file "hello.txt"
    (lambda (i)
        (let* ((a (read-char i))
               (b (read-char i))
               (c (read-char i)))
            (list a b c))))
;;; (#\h #\e #\l)
