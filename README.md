# Alliance-IT
Тестовые задание. 

В файле test1.cpp решена задача 1.
Метод сравнивает две std::string которые содержат код авиакомпании и номер рейса. Возвращается результат сравнения.
В данном методе не проверяется, соответствуют ли входные строки предоставленному формату кода авиакомпании и номера рейса.

В файле test2.cpp решена задача 2.
В двух потоках считываются строки с кодом и номером рейса из файлов (1_in.txt, 2_in.txt).
В выходные файлы (1_out.txt, 2_out.txt) записываются неуникальные комбинации авиакомпании и номера рейса.
Если считанная из файла комбинация авиакомпании и номера рейса не соответствует формату, описанному в задаче 1, то данная строка пропускается и не записывается в выходной файл.
