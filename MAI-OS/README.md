  Лабораторные работы по курсу "Операционные системы". Лектор - Миронов Евгений Сергеевич (Касперский).

  Московский авационный институт, прикладная математика и информатика, 3 семестр, 2021 год.

  ```ЛР 1: вывод утилиты strace на примере ЛР4, описание системных вызовов.```




  ```ЛР 2: взаимодействие между процессами при помощи каналов pipe, использование fork().```

  Вариант 17.
  Правило фильтрации: строки длины больше 10 символов отправляются в pipe2, иначе в pipe1. Дочерние процессы удаляют все гласные из строк.




 ```ЛР 3: введение в многопоточное программирование.```

  Вариант 13.
  Есть набор 128 битных чисел, записанных в шестнадцатеричном представлении, хранящихся в файле. Необходимо посчитать их среднее арифметическое. Округлить результат до целых.
  Количество используемой оперативной памяти должно задаваться "ключом".




  ```ЛР 4: взаимодйствие между процессами при помощи концепции memory map.```

  Вариант 17.
  Правило фильтрации: строки длины больше 10 символов отправляются в один процесс через memory-map, больше 10 символов в другой процесс через memory map. Дочерние процессы     удаляют все гласные из строк. 




  ```ЛР 5: создание динамических библиотек и работа с ними.```

  Вариант 31.
  Требуется создать динамические библиотеки, которые реализуют определенный функционал. Далее использовать данные библиотеки 2-мя способами:
  1. Во время компиляции (на этапе «линковки»/linking)
  2. Во время исполнения программы. Библиотеки загружаются в память с помощью интерфейса ОС для работы с динамическими библиотекам

  Функции по варианту: рассчет значения числа е(основание натурального логарифма), подсчет площади плоской геометрической фигуры по двум сторонам.
  



  ```ЛР 6: понятие об очередях сообщений, пара сервер-клиент, работающая на zero message queue (ZMQ).```

  Вариант 44.
  Требуется реализовать распределенную систему по асинхронной обработке запросов. В данной
  распределенной системе должно существовать 2 вида узлов: «управляющий» и
  «вычислительный». Необходимо объединить данные узлы в соответствии с той топологией,
  которая определена вариантом. Связь между узлами необходимо осуществить при помощи
  технологии очередей сообщений. Также в данной системе необходимо предусмотреть проверку
  доступности узлов в соответствии с вариантом. При убийстве («kill -9») любого вычислительного
  узла система должна пытаться максимально сохранять свою работоспособность, а именно все
  дочерние узлы убитого узла могут стать недоступными, но родительские узлы должны сохранить
  свою работоспособность.

  Топология: идеально сбалансированное бинарное дерево

  Список команд по варианту: подсчет суммы чисел exec id k n1 n2... nk, проверка доступности вычислительного узла heartbeat time





  ```Курсовой проект: отработка навыков, полученных за курс "Операционные системы"```

  Вариант 5.
  Реализация клиент-серверной игры "Морской бой" при помощи концепции memory-map, работа с примитивом синхронизации mutex.
 
