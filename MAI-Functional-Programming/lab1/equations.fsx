// Define functions to solve algebraic equations
// Варианты функций 16-18
let epsilon: float = 0.000001

let rec dichotomy f (a: float) (b: float) (epsilon: float) = 
    let c = (a + b) / 2.
    if (abs (f c) >= epsilon) then
        if (f a * f c < 0) then
            dichotomy f a c epsilon
        else
            dichotomy f c b epsilon
    else 
        c

let rec iterations phi x0 epsilon = 
    let c = phi x0
    if (abs(x0 - c)) >= epsilon then
        iterations phi c epsilon
    else
        x0

let newthon f f' x0 epsilon =
    let phi x = x - (f x / f' x)
    iterations phi x0 epsilon

// Solve 3 equations using three methods defined above
let f1 (x: float) = 3. * sin(sqrt(x)) + 0.35 * x - 3.8
let f2 (x: float) = 0.25 * x * x * x + x - 1.2502
let f3 (x: float) = x + sqrt(x) + System.Math.Cbrt(x) - 2.5

let f1' (x: float) = ((3. * cos(sqrt(x))) / (2. * sqrt(x))) + 0.35
let f2' (x: float) = 0.75 * x * x + 1.
let f3' (x: float) = ((3. * System.Math.Pow(x, 2.0/3.0) + 2. * sqrt(x)) / (6. * System.Math.Pow(x, 7.0/6.0))) + 1.

let phi1 (x: float) = (3.8 - 3. * sin(sqrt(x))) / 0.35
let phi2 (x: float) = 1.2502 - 0.25 * x * x * x
let phi3 (x: float) = (2.5 / (1. + (sqrt(x)) + x ** (-1. / 6.))) ** 2.
let main = 
    printfn "%10.4f  %10.4f  %10.4f" (dichotomy f1 2. 3. epsilon) (iterations phi1 2. epsilon) (newthon f1 f1' 2. epsilon)
    printfn "%10.4f  %10.4f  %10.4f" (dichotomy f2 0. 2. epsilon) (iterations phi2 0. epsilon) (newthon f2 f2' 0. epsilon)
    printfn "%10.4f  %10.4f  %10.4f" (dichotomy f3 0.4 1. epsilon) (iterations phi3 0.4 epsilon) (newthon f3 f3' 0.4 epsilon)

    
