;half22 for 208
(define (root a b)
 (define temp 0)
 (set! temp (half-interval a b (f a)(f b)))
  (display"Total number of iteranions=")
  (display total-iterations)(newline)
 (display"[")
 (display a)
 (display" , ")
 (display b)
 (display"]")
      temp 
)
(define (half-interval a b fa fb)
 (define root 0)
 (set! total-iterations 0)
   (set! root(cond((and(< fa 0)(> fb 0))
                 (try a b))
         ((and(> fa 0)(< fb 0))
                 (try b a))
         (else(+ b 1)))
    )
  (newline)
  root
) 
(define(try neg-point pos-point)
 (define midpoint 0)
 (define test-value 0)
     (set! midpoint (average neg-point pos-point))
     (cond((close-enough? neg-point pos-point) midpoint)
          (else (set! test-value (f midpoint))
               (display "+")
               (set! total-iterations (+ total-iterations 1))
               (cond((> test-value 0)(try neg-point midpoint))
                    ((< test-value 0)(try midpoint pos-point))
                    (else midpoint))
          )
     )
)
(define (close-enough? x y)
  (<(abs (- x y))tolerance))
(define (average x y)(*(+ x y)(/ (* 2.0))))

(define tolerance 0.001)
(define total-iterations 0)
(define(f z)
  (- (+ (sin (- z (* 0.25 pi))) (log z)) 0.8)
  )
 (display"Variant 208-16\n")
;      a b
 (root 5.3 6.0)
 (display"(c) Morozov Artem 2022\n")