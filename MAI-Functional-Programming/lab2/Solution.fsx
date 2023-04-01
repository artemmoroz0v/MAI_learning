// Part 1
// 16 вариант - произведение минимального и максимального элементов списка 
let list = [11; 22; 33; 44; 55; 66; 77; 88; 99; 100]


// Method 1: Library Function 
let libraryFunction list = 
    let min = list |> Seq.min
    let max = list |> Seq.max
    min * max
printfn "Method 1: Library Function\t%d\n" (libraryFunction list)


// Method 2: Recursion
let rec Recursion (list: int list) =
    let rec auxilliaryFunction (min:int) (max:int) = function
        | [] -> min * max
        | x::xs -> 
            let newMin = if x < min then x else min
            let newMax = if x > max then x else max
            auxilliaryFunction newMin newMax xs
    match list with
    | [] -> failwith "List is empty"
    | x::xs -> auxilliaryFunction x x xs
printfn "Method 2: Recursion\t%d\n" (Recursion list)


// Method 3: Tail recursion
let rec tailRecursion list =
    match list with
    | [] -> failwith "The list is empty!"
    | [x] -> (x, x)
    | head::tail -> 
        let (min, max) = tailRecursion tail
        if head < min then (head, max)
        elif head > max then (min, head)
        else (min, max)
let (min, max) = tailRecursion list
let result = min * max
printfn "Method 3: Tail Recursion\t%d\n" (result)
