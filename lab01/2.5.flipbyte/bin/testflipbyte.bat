REM ==================================================================
REM некорректные параметры
REM ++++++++++++++++++++++++++++
REM количество аргументов
REM без аргументов
flipbyte > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM слишком много аргументов
flipbyte 1 2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 2param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM содержание аргумента
REM меньше 0
flipbyte -10 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output lesszero.txt
IF ERRORLEVEL 1 GOTO err

REM больше 255
flipbyte 256 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output outofbyte.txt
IF ERRORLEVEL 1 GOTO err

REM содержит пробелы и табуляцию
REM ---------------------
REM пробелы
flipbyte " 	 2	 " > output
IF ERRORLEVEL 1 GOTO err
FC /B output 2.txt
IF ERRORLEVEL 1 GOTO err

REM только пробелы
flipbyte " 	 " > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM не десятичное число
REM ---------------------
REM дробное число
flipbyte 12.2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM начинается не с цифры
flipbyte F1 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM содержит не цифру внутри
flipbyte 1F1 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM последний символ не цифра
flipbyte 1F > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM проверка правильности выполнения преобразований
REM 0 -> 0
flipbyte 0 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 0.txt
IF ERRORLEVEL 1 GOTO err

REM 255 -> 255
flipbyte 255 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 255.txt
IF ERRORLEVEL 1 GOTO err

REM +25 -> 152
flipbyte +25 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 25.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit