REM ошибки во введённых данных 
type test\input_errors.txt | findmaxex > test\stdout
FC /B test\stdout test\output_errors.txt
IF ERRORLEVEL 1 GOTO err

REM пустой список
type test\input_emptylist.txt | findmaxex > test\stdout 
FC /B test\stdout test\output_emptylist.txt
IF ERRORLEVEL 1 GOTO err

REM одна запись
type test\input_1entry.txt | findmaxex > test\stdout
FC /B test\stdout test\output_1entry.txt
IF ERRORLEVEL 1 GOTO err

REM две записи
type test\input_2entries.txt | findmaxex > test\stdout
FC /B test\stdout test\output_2entries.txt
IF ERRORLEVEL 1 GOTO err

REM три записи
type test\input_3entries.txt | findmaxex > test\stdout
FC /B test\stdout test\output_3entries.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit