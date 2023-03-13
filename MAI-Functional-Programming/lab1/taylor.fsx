// Print a table of a given function f, computed by taylor series

// function to compute
let f x = (1. + 2. * x * x) * (exp(x * x))

let a = 0.0
let b = 1.0
let n = 10
let epsilon = 0.000001

//факториал из лекции
let rec fact' (acc: float) =
    function
    | (n: float) when n = 0 -> acc
    | n when n = 1 -> acc
    | n -> fact' (acc * n) (n - 1.)

let fact x = fact' 1 x

// Define a function to compute f using naive taylor series method
let rec taylor_naive (x: float) (n: float) (i: float) (acc: float) (epsilon: float) =
    let prev = ((2. * i - 1.) / (float (fact(i - 1.)))) * (x ** (2. * i - 2.)) //i-1-член
    let cur = ((2. * i + 1.) / (float (fact(i)))) * (x ** (2. * i)) //i-тый член
    if (abs(cur - prev) < epsilon) then //если меньше эпсилон, то возвращаем член и итерацию
        (acc, i)
    else //иначе рекурсия для i+1 члена...
        let acc = acc + prev
        taylor_naive x n (i + 1.) acc epsilon


// Define a function to do the same in a more efficient way
let rec taylor_smart (x: float) (n: float) (i: float) (acc: float) (prev: float) (epsilon: float) = 
    let quotitent: float = (((x ** 2.) * (2. * i + 1.)) / (i * (2. * i - 1.))) //частное i и i-1 члена
    if (abs(quotitent * prev - prev) < epsilon) then //если меньше эпсилон, то возвращаем член и итерацию
        (acc, i)
    else //иначе рекурсия для i+1 члена...
        let prev = prev * quotitent
        let acc = acc + prev
        taylor_smart x n (i + 1.) acc prev epsilon

let main =
   for i=0 to n do
     let x = a+(float i)/(float n)*(b-a)
     let (taylor_naive_res, taylor_naive_iter) = taylor_naive x i 1. 0 epsilon
     let (taylor_smart_res: float, taylor_smart_iter: float) = taylor_smart x i 1. 1 1 epsilon
     printfn "%5.2f   %10.6f  %10.6f %0.0f\t %10.6f %0.0f" x (f x) taylor_naive_res taylor_naive_iter taylor_smart_res taylor_smart_iter //без табуляции кривой вывод
// make sure to improve this table to include the required number of iterations
// for each of the methods

main
