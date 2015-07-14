REM некорректные параметры
REM ++++++++++++++++++++++++++++
REM количество аргументов
REM без аргументов
sets.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM слишком много аргументов
sets.exe 1 2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2params.txt
IF ERRORLEVEL 1 GOTO err


REM содержание аргумента
REM аргумент не число
sets.exe twenty > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notint.txt
IF ERRORLEVEL 1 GOTO err

REM аргумент не целое число
sets.exe 1.1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notint.txt
IF ERRORLEVEL 1 GOTO err

REM аргумент < 1
sets.exe 0 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notpositive.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM корректная работа
sets.exe 5 > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\5.txt
IF ERRORLEVEL 1 GOTO err

sets.exe 100 > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\100.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit