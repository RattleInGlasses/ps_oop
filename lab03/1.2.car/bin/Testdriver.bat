type test\input_normal.txt | driver.exe > test\out
IF ERRORLEVEL 1 GOTO err
FC /B test\out_normal.txt test\out
IF ERRORLEVEL 1 GOTO err

REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit