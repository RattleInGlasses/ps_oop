REM некорректные параметры
REM ++++++++++++++++++++++++++++
REM количество аргументов
REM без аргументов
invert > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM слишком много аргументов
invert 1 2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 2param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM содержание аргумента
REM невозможно открыть файл
invert nosuchfile.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output cantopen.txt
IF ERRORLEVEL 1 GOTO err

REM некорректный файл
REM пустой файл
invert empty.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM содержит не только числа
REM нецифровой символ в начале числа
invert brokenmatrix1.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM нецифровой символ в середине числа
invert brokenmatrix2.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM нецифровой символ после числа
invert brokenmatrix3.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM неправильный размер матрицы
invert wrongmatrix.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM проверка правильности выполнения преобразований
invert matrix1.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted1.txt
IF ERRORLEVEL 1 GOTO err

invert matrix2.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted2.txt
IF ERRORLEVEL 1 GOTO err

invert matrix3.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted3.txt
IF ERRORLEVEL 1 GOTO err

invert "martrix4 (notInvertable).txt" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output cantinvert.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit