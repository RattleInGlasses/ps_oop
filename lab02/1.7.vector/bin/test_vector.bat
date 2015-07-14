REM 3 целых числа
type test\3int.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_3int.txt
IF ERRORLEVEL 1 GOTO err

REM 3 вещественных числа
type test\3real.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_3real.txt
IF ERRORLEVEL 1 GOTO err

REM 6 вещественных чисел
type test\6real.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_6real.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit