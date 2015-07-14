REM пустой входной поток
type test\empty.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\empty.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток из перевода строка
type test\newline.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_newline.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток из одного символа
type test\1sym.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_1sym.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток без лишних пробелов
type test\no_extra_spaces.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_no_extra_spaces.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток c лишними пробелами
type test\strings_with_extra_spaces.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_strings_with_extra_spaces.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit