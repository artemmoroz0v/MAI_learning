# Отчет по лабораторной работе №1
## Работа со списками и реляционным представлением данных
## по курсу "Логическое программирование"

### студент: Морозов А.Б.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|   21.10      |      5        |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*

Предикат 1.1.: при реализации через стандартные лучше обойтись без member (лишний рекурсивный проход по списку). При переносе отсечения (!) за append предикат member можно не использовать, append завершается удачно только в случае принадлежности Х списку: del_standart(L, X, R) :-   append(R, [X|_], L),! 


## Введение

Список в языке программирования Пролог -  это некая последовательность из элементов (упорядоченная), имеющая, зачастую, произвольную длину, причем нельзя пренебрегать порядком элементов. Хоть при работе со списками и не указывается конкретный тип данных внутри него, однако необходимо, чтобы все элементы списка имели единый тип. Элементами списка могут быть любые термы – переменные, константы, цифры и так далее.

Списки похожи на известные всем структуры данных: стек, динамический массив (вектор), статический массив. Они похожи и на списки, которые мы привыкли видеть в императивных языках программирования. Однако списки в языке Пролог все же имеют отличия от привычных подходов хранения данных в других языках: список в Прологе не требует указания размерности и типа данных его элементов до начала использования. Помимо этого, "Пролог" довольно необычно представляет списки в формате "[Голова|Хвост]" ([Head|Tail]).

## Задание 1.1: Предикат обработки списка

del_standart(L, X, R) - предикат обработки списка, реализованный через стандартные предикаты. del_standart принимает некий список (например, [1,2,3,4,5,6]) и "ключ", или значение, начиная с которого надо отделить хвост списка. В итоге получается новый список R, в котором, начиная с заданного значения, отделен хвост. Идея состоит в том, что мы сначала проверяем список на наличие конкретного элемента через стандартный предикат member, а далее через предикат append происходит конкатенация списков, в результате которой отсеивается список, идущий после конкретного элемента.


del_recursive([H|T], X, [H|R]) - тот же самый предикат обработки списка, только реализованный рекурсивно. Прописываем условие, что удаление элемента Х из пустого списка - это пустой список. Следующий предикат: удаление элемента Х из списка вида [X|T] - это пустой список. Далее запускаем предикат рекурсивно.

Примеры использования:
```prolog
?-del_standart([1,2,3,4,5,6,7,8,9], 5, X).
X=[1,2,3,4].
?-del_standart([1,2,3], 3, X).
X=[1,2].
?-del_recursive([1], 1, X).
X=[].
?-del_recursive([1,2,3,4],4,X).
X=[1,2,3].
```

Реализация:
```prolog
del_standart(L, X, R) :- member(X, L), !, append(R, [X|_], L).
del_standart(L, X, R) :- append(R, [], L).

del_recursive([], X, []) :- !.
del_recursive([X|T], X, []) :- !.
del_recursive([H|T], X, [H|R]) :- del_recursive(T, X, R).
```

## Задание 1.2: Предикат обработки числового списка

multiplication_standart([X, Y|T], P) - предикат обработки числового списка, реализованный через стандартные предикаты. Идея заключается в том, что мы паре чисел сопоставляем их произведение. 


multiplication_recursive([Head|Tail], Result) - тот же самый предикат обработки числового списка, реализованный рекурсивно. Для начала задаем условие, что произведение в пустом списке равняется единице. После рекурсивно углубляемся в конец списка и начинаем перемножать элементы с конца, умножая результат в хвосте списка на голову списка.

Примеры использования:
```prolog
?-multiplication_standart([1,2,3,4,5],L), write(L).
X=120.
?-multiplication_standart([1,2,3],L), write(L).
X=6.
?-multiplication_recursive([],L), write(L).
X=1.
?-multiplication_recursive([1,2,3,4],L), write(L).
X=24.
```

Реализация:
```prolog
multiplication_standart([], 1):- !.
multiplication_standart([0|_], 0):- !.
multiplication_standart([X], X):- !.
multiplication_standart([X, Y|T], P):- PC is X * Y, remove(X, [X, Y|T], L1), remove(Y, L1, L2), append([PC], L2, L3), multiplication_standart(L3, P).


multiplication_recursive([], 1):-!.
multiplication_recursive([Head|Tail], Result):-multiplication_recursive(Tail, TailRes), Result is TailRes * Head.
```

## Задание 1.3: Пример совместного использования предикатов.

В качестве примера я написал предикат example, который принимает два списка, удаляет из них хвосты, начиная с конкретного значения, далее склеивает их и выводит новый список пользователю.


example(L1, X1, L2, X2):-del_standart(L1, X1, L), del_standart(L2, X2, R), append(L, R, Result), write(Result).

Примеры использования:
```prolog
?-example([1,2,3],3,[4,5,6],6).
Result = [1,2,4,5].
?-example([1,2,3,4,5,6],4,[7,8,9,10],9).
Result = [1,2,3,7,8].
```

## Задание 2: Реляционное представление данных

Наверное, неоспоримым и одновременно главным преимуществом реляционного представления является удобный поиск необходимой информации, ведь такое представление отображает информацию в наиболее простой для пользователя форме, позволяет легко добавлять новую и удалять ненужную информацию, узнавать связи тех или иных объектов. Помимо этого, требуется меньше преобразований, чтобы в благоприятном виде отобразить данные. Однако есть и недостатки: довольно медленный доступ к данным (он удобен с точки зрения понимания места поиска, но иногда занимает много времени), а также возможные трудности, возникающие при работе с чересчур большими размерами информации.

Первый пункт: получить таблицу групп и средний балл по каждой из групп.
Для этого мною реализован предикат set_group, использующий стандартный предикат findall - он работает с нашей базой данных, при этом сортируя студентов по спискам групп.

Примеры использования:
```prolog
?-set_group(101, Result).
Result = ['Петровский', 'Сидоров', 'Мышин', 'Безумников', 'Густобуквенникова'].

?-set_group(102, Result).
Result = ['Петров', 'Ивановский', 'Биткоинов', 'Шарпин', 'Эксель', 'Текстописов', 'Криптовалютников', 'Азурин', 'Круглотличников'].

?-set_group (103, Result).
Result = ['Сидоркин', 'Эфиркина', 'Сиплюсплюсов', 'Программиро', 'Клавиатурникова', 'Решетников', 'Текстописова', 'Вебсервисов'].

?-set_group (104, Result).
Result = ['Иванов', 'Запорожцев', 'Джаво', 'Фулл', 'Круглосчиталкин', 'Блокчейнис'].
```

После предиката set_group я также реализовал предикат set_table, который принимает список номеров групп, а после находит всех студентов для каждой группы при помощи уже знакомого нам findall. При помощи стандартного предикакта asserta в базу данных добавляется факт о принадлежности студента к группе (возвращаемся к предикату set_group), а пользователю выводятся номера всех групп и соответствующие списки студентов. 

Примеры использования:
```prolog
?- set_table([101]).
101: [Петровский, Сидоров, Мышин, Безумников, Густобуквенникова].

?- set_table([102]).
102: [Петров, Ивановский, Биткоинов, Шарпин, Эксель, Текстописов, Криптовалютников, Азурин, Круглотличников].

?- set_table([103]).
103: [Сидоркин, Эфиркина, Сиплюсплюсов, Программиро, Клавиатурникова, Решетников, Текстописова, Вебсервисов].

?- set_table([104]).
104: [Иванов, Запорожцев, Джаво, Фулл, Круглосчиталкин, Блокчейнис].
```


Предикат average_grade_in_group, требующийся по заданию, отвечает за нахождение среднего балла по группе. Он при помощи bagof ищет в базе данных количество получений каждой оценки в группе. 

ПРИМЕЧАНИЕ: bagof - то же самое, что и findall, выдающий неуспех при пустом списке). 

Чтобы реализовать данный предикат, нам требуется вспомогательный предикат amount_of_grades, отвечающий за количество получений каждой оценки в группе. На основе полученных данных вычисляется сумма баллов (длина каждого списка, умноженная на оценку) и делится на общее количество оценок (сумма длин всех списков с оценками). Полученный результат - искомый средний балл заданной группы.

Примеры использования:
```prolog
?- average_grade_in_group(101, Result).
Result = 3.9.

?- average_grade_in_group(102, Result).
Result = 3.7777777777777777.

?- average_grade_in_group(103, Result).
Result = 3.7708333333333335.

?- average_grade_in_group(104, Result).
Result = 3.861111111111111.
```

Второй пункт: для каждого предмета получить список студентов, не сдавших экзамен (grade=2).
Для реализации этого пункта я разработал предикат subjects_with_bad_marks. Предикат использует bagof для нахождения имен студентов, получивших двойку (grade(X, Subject, 2)).
После выполнения предиката пользователь получит список студентов с двойками.

Примеры использования:
```prolog
?- subjects_with_bad_marks.'INF', Res).
Res = ['Эфиркина', 'Джаво', 'Безумников'].

?- subjects_with_bad_marks('MTH', Res).
Res = ['Запорожцев', 'Круглосчиталкин', 'Густобуквенникова', 'Криптовалютников', 'Блокчейнис', 'Азурин'].

?- subjects_with_bad_marks('ENG', Res).
Res = ['Эфиркина'].

?- subjects_with_bad_marks('LP', Res).
Res = ['Запорожцев', 'Эфиркина', 'Текстописов'].
```

Третий пункт: найти количество не сдавших студентов в каждой из групп.
Для начала я реализовал предикат definition_of_fail_student, чтобы понимать, какой именно студент считается несдавшим экзамен. Далее предикат amount_of_fail_students, требующийся по заданию, при помощи setof получает весь список студентов, удовлетворяющих предикату definition_of_fail_student. Длина списка не сдавших студентов и является искомым ответом. 

ПРИМЕЧАНИЕ: setof получает отсортированный список (то есть без повторений и элементов). 
Этим он отличается от bagof и findall.

Примеры использования:
```prolog
?- amount_of_fail_students(101, Res).
Res = 2.

?- amount_of_fail_students(102, Res).
Res = 4.

?- amount_of_fail_students(103, Res).
Res = 3.

?- amount_of_fail_students(104, Res).
Res = 4.
```


## Выводы (+++)

Данная лабораторная работа - мое первое творение, относящееся к парадигме логического программирования. Язык программирования Пролог открыл для меня неизведанный ранее мир и помог абстрагироваться от привычных концепций объектно-ориентированного и параллельного программирования, позволив окунуться в иную среду программирования, подчиняющуюся своим законам и правилам.


Пролог, на мой взгляд, является очень интересным языком, ведь в его основе лежит такое важное понятие информатики, как рекурсия.  Лабораторная работа №1, прежде всего, ознакомила меня с базовыми вещами языка: стандартными предикатами и списками. Я научился реализовывать стандартные предикаты несколькими способами, а также подходить к выполнению поставленной задачи, анализируя ее с разных точек зрения: с точки зрения рекурсивного подхода и с точки зрения подхода, предполагающего стандартные предикаты.
Списки в языке Пролог позволяют человеку, работающему, в основном, с низкоуровневыми языками программирования, взглянуть на структуры данных с новой стороны. Мне очень понравилась концепция представления списка в формате [Head|Tail].


Более того, данная лабораторная работа позволила мне понять глубже принципы декларативного программирования, которое описывает, что представляет собой проблема и ожидаемый результат, в отличие от императивного, которое описывает, как решить задачу и предоставить нужный результат. Довольно интересно сравнить два этих принципа: с одной стороны, императивные языки программирования более просты для понимания, имеют очень широкое применение, но декларативный принцип программирования, на мой взгляд, больше императивнго склонен к тому, чтобы сделать сложные вещи очень простыми.


В заключение хотелось бы отметить, что проделанная лабораторная работа побудила меня гораздо глубже рассмотреть реляционное и нереляционное представление информации в базе данных. Уверен, что и следующие лабораторные работы по языку программирования Пролог будут служить для меня мотивацией изучать что-то новое, открывать неизвестные просторы программирования, развивать себя, как человека, который гордо будет представлять сферу IT-технологий.