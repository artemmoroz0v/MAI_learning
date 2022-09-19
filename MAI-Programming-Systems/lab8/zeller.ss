;zeller.ss for 208
(define (day-of-week)
 (zeller dd
      (+ 8(cond((>= 2 mm)(+ mm 2)) (else (- mm 010))))
      (remainder (+ 1(cond((not(or(not(>= 3 mm))(= mm 3)))(- yyyy 2))(else (- yyyy 1))))
                 100)
      (quotient (cond((>= 2 mm)(- yyyy 1))(else yyyy))
                100)
 )
)
(define (zeller d m y c)
 (neg-to-pos (remainder (+ d y
                          (quotient (-(* 26 m)2) 10)
                          (quotient y 4)
                          (quotient c 4)
                          (* 2(- c))
                       )
            7)
 )
)
(define (neg-to-pos d)
 (cond((not(>= d 0))(+ d 7))
      (else d)
 )
)
(define (birthday dw)
;                  ^{0,...,6}
 (display "Artem Morozov was born on ")
      (display
          (if(= dw 0)"Sunday "
             (if(= dw 1)"Monday "
                (if(= dw 2)"Tuesday "
                   (if(= dw 3)"Wednesday "
                      (if(= dw 4)"Thursday "
                         (if(= dw 5)"Friday "
                              "Saturday "))))))
)
  (display dd)(display ".")
  (display mm)(display ".")
 yyyy
)
(define dd 7)
(define mm 5)
(define yyyy 2002)
(birthday (day-of-week))
