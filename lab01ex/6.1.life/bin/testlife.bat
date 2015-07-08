REM параметры
REM запуск без параметров
life.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с 3-мя параметрами
life.exe input.txt out.txt andonemore > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_3args.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки открытия файлов
REM не открывает input
life.exe test\nosuchfile.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM не открывает output
life.exe test\input_empty.txt 1ds:\ttt.xt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки входного файла
REM пустой файл
life.exe test\input_empty.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0w.txt
IF ERRORLEVEL 1 GOTO err

REM незаконченный файл
life.exe test\input_unfinished.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noend.txt
IF ERRORLEVEL 1 GOTO err

REM неправильные символы
life.exe test\input_invalidsym.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_invalidsym.txt
IF ERRORLEVEL 1 GOTO err

REM -----------------------------------------------------
REM размер поля
REM слишком большое поле
REM большая ширина
life.exe test\input_257w.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_bigw.txt
IF ERRORLEVEL 1 GOTO err

REM предел ширины
life.exe test\input_256w.txt test\out_256w.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\input_256w.txt test\out_256w.txt
IF ERRORLEVEL 1 GOTO err

REM большая высота
life.exe test\input_257h.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_bigh.txt
IF ERRORLEVEL 1 GOTO err

REM предел высоты
life.exe test\input_256h.txt test\out_256h.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\input_256h.txt test\out_256h.txt
IF ERRORLEVEL 1 GOTO err


REM слишком маленькое поле
REM нулевая ширина
life.exe test\input_0w.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0w.txt
IF ERRORLEVEL 1 GOTO err

REM нулевая высота
life.exe test\input_0h.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0h.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM направление вывода
REM вывод в текстовый файл
life.exe test\input1.txt test\out_1.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_1.txt test\out_standard1.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM вывод в stdout
life.exe test\input1.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_standard1_stdout.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM правильность вычислений
REM пустое поле
life.exe test\input_emptyfield.txt test\out_emptyfield.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_emptyfield.txt test\out_emptyfield.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM второй тест
life.exe test\input2.txt test\out_2.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_2.txt test\out_standard2.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM третий тест
life.exe test\input3.txt test\out_3.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_3.txt test\out_standard3.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit