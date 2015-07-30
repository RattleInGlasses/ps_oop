REM некорректные параметры
REM ++++++++++++++++++++++++++++
REM количество аргументов
REM без аргументов
rectangles > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM 1 аргумент
rectangles 1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_1param.txt
IF ERRORLEVEL 1 GOTO err

REM слишком много аргументов
rectangles 1 2 3 4 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_4param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM содержание аргумента
REM невозможно открыть первый файл
rectangles nosuchfile.txt test\input11.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_cantopen1.txt
IF ERRORLEVEL 1 GOTO err

REM невозможно открыть второй файл
rectangles test\input11.txt nosuchfile.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_cantopen2.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM особые случаи
REM пустой файл
rectangles test\input_empty.txt test\input_empty.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_empty.txt
IF ERRORLEVEL 1 GOTO err

REM файл с пустой строкой
rectangles test\input_newline.txt test\input_newline.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_empty.txt
IF ERRORLEVEL 1 GOTO err

REM ошибка в первом файле
rectangles test\input_error.txt test\input_newline.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_error1file.txt
IF ERRORLEVEL 1 GOTO err

REM ошибка во втором файле
rectangles test\input_newline.txt test\input_error.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_error1file.txt
IF ERRORLEVEL 1 GOTO err

REM графика в output
rectangles test\input11.txt test\input12.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_full1.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM проверка правильности обработки
rectangles test\input11.txt test\input12.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic1.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text1.txt
IF ERRORLEVEL 1 GOTO err

rectangles test\input21.txt test\input22.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic2.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text2.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit