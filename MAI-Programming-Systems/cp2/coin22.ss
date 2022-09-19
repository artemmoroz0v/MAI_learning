(define (largest coins-set)
  (cond
          ((= coins-set 1) 3)
          ((= coins-set 2) 5)
          ((= coins-set 3) 20)
          ((= coins-set 4) 25)
          (else 0)
     )
)

(define (count-change amount)
  (display "______") (newline) (display " amount: ")
  (display amount)
      (newline)
  (display "COINS: ")
  (display COINS)
      (newline)
  (cond
         ((or (>= 0 amount) (not(>= COINS 1)) (= (largest COINS) 0)) ( let() (display "Improper parameter value!\ncount-change= ") -1))
         (else (display "List of coin denominations: ") (denomination-list COINS) (display "count-change= ") (cc amount COINS))
  )
)


(define (Shaeffer? x? y?)
  (or (not x?) (not y?))
)

(define (cc amount coins-set)
  (cond
    ((= amount 0) 1)
    ((Shaeffer? (>= amount 1) (not(>= 0 coins-set))) 0)
    (else (+ (cc amount (- coins-set 1)) (cc (- amount (largest coins-set)) coins-set)))
  )
)

(define (denomination-list coins-set)
  (cond
    ((= coins-set 0) (let() (newline) 0))
    (else (display (largest coins-set)) (display " ") (denomination-list (- coins-set 1)))
   )
)

(define VARIANT 16)
(define COINS 4)
(display "Variant ")
(display VARIANT)
(newline)
(display (count-change 100))(newline)
(set! COINS 13)
(display (count-change 100))(newline)
(display "(c) Artem Morozov 2022")
(newline)