// Part 2
// Вариант 2:
// Напечатайте среднюю оценку за каждый предмет
// Для каждой группы, напечатайте список студентов, заваливших сессию (хотя бы одна оценка = 2)
// Для каждого студента, найдите среднюю оценку
#load "One.fsx"
open One

let constNewLine = "\n"

//Task 1. Find average mark for each subject
printfn "%s" "Task 1. Average grade for each subject:"
let avgGradeForSubject (subjectAbbr: string) =
    Data.marks
    |> List.filter (fun (_, subj, _) -> subj = subjectAbbr)
    |> List.averageBy (fun (_, _, grade: float) -> grade)
for subjectAbbr, subjectName in Data.subjs do
    let avgGrade: float = avgGradeForSubject subjectAbbr
    printfn "Average grade for subject %s (%s) is: %.2f" subjectName subjectAbbr avgGrade
printfn "%s" constNewLine


//Task 2. Print a list of students who failed the session for each group
printfn "%s" "Task 2. Print a list of students who failed the session for each group:"
let failedStudents group =
    Data.marks
    |> Seq.filter (fun (_, _, grade) -> grade <= 2)
    |> Seq.filter (fun (surname, _, _) -> Data.studs |> Seq.exists (fun (s, g) -> s = surname && g = group))
    |> Seq.map (fun (surname, subject, _) -> (surname, subject))
    |> Seq.groupBy (fun (_, subject) -> subject)
    |> Seq.map (fun (subject, students) -> (subject, students |> Seq.map fst |> Seq.toList))
    |> List.ofSeq
for group: int in Data.studs |> List.map snd |> List.distinct do
    printfn "Students who failed the session in group № %d are:" group
    let failedStudents = failedStudents group
    for (_, students) in failedStudents do
        printfn "%A" students
printfn "%s" constNewLine


//Task 3. Find average grade for each student
printfn "%s" "Task 3. Average grade for each student:"
let gradesByStudent =
    Data.marks |> List.groupBy (fun (name, _, _) -> name)
let averageGradeForStudent grades =
    grades |> List.averageBy (fun (_, _, grade) -> grade)
for (name, _) in Data.studs do
    let studentGrades =
        gradesByStudent
        |> List.tryFind (fun (n, _) -> n = name)
        |> Option.map (fun (_, grades) -> grades)
        |> Option.defaultValue []
    let average = averageGradeForStudent studentGrades
    printfn "Average grade for student %s is: %f" name average
printfn "%s" constNewLine
