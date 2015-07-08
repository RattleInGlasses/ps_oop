REM количество параметров
REM запуск без параметров
replace > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с одним параметром
replace infile.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 1param.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с пятью параметрами
replace replace infile.txt outfile.txt string param5 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 5param.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM пустые строки
REM пустая строка в имени input
replace "" "" > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output noinput.txt
IF ERRORLEVEL 1 GOTO err

REM пустая строка в имени output
replace infile.txt "" > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output nooutput.txt
IF ERRORLEVEL 1 GOTO err

REM пустая строка вместо искомой строки
replace infile.txt outfile.txt "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM пустая строка вместо искомой и заменяющей строк
replace infile.txt outfile.txt "" "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM пустая строка вместо заменяющей строки
replace infile.txt outfile.txt file "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outNullReplaced.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM файлы
REM пустой файл копирование
replace empty.txt outfile.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodEmptyExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt empty.txt
IF ERRORLEVEL 1 GOTO err

REM пустой файл копирование и замена
replace empty.txt outfile.txt file life > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodEmptyExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt empty.txt
IF ERRORLEVEL 1 GOTO err

REM в файле нечего заменять
replace infile.txt outfile.txt youcantfindit smth > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM замена на строку, повторяющую исходную
replace infile.txt outfile.txt file filefile > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outWordWord.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM нормальная работа
REM запуск с двумя параметрами (копирование)
replace infile.txt outfile.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с тремя параметрами (не задана заменяющая строка - в этом случае происходит удаление искомой строки)
replace infile.txt outfile.txt file
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outNullReplaced.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с четыремя параметрами (обычная работа)
replace infile.txt outfile.txt file life
if NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outReplaced.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit