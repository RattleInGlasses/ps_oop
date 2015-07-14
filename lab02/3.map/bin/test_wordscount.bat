REM пустой входной поток
type test\empty.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\empty.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток из одного слова
type test\1word.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_1word.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток из разных слов
type test\severalwords.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_severalwords.txt
IF ERRORLEVEL 1 GOTO err

REM входной поток из с повторяющимися словами
type test\repeated.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_repeated.txt
IF ERRORLEVEL 1 GOTO err

REM слова в разном регистре
type test\wORds.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_wORds.txt
IF ERRORLEVEL 1 GOTO err



REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit