REM некорректные параметры
REM ++++++++++++++++++++++++++++
REM количество аргументов
REM без аргументов
expand_template.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM недостаточно аргументов
expand_template.exe input > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_1param.txt
IF ERRORLEVEL 1 GOTO err

REM нечётное количество аргументов
expand_template.exe input output param > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_oddparams.txt
IF ERRORLEVEL 1 GOTO err

expand_template.exe input output param1 value1 param2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_oddparams.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки открытия файлов
REM не открывает input
expand_template.exe test\nosuchfile.txt test\output.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM не открывает output
expand_template.exe test\input_empty.txt "D:/:\D\out.txt" > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM пустые строки
REM замена пустой строки (просто копирование)
expand_template.exe test\input_copy.txt test\out_copy.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_copy.txt test\correct_out_copy.txt
IF ERRORLEVEL 1 GOTO err

REM замена на пустую строку (удаление искомой строки)
expand_template.exe test\input_nullvalue.txt test\out_nullvalue.txt ЛИШНЕЕ ""
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_nullvalue.txt test\correct_out_nullvalue.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM вывод сообщения об успешном завершении
expand_template.exe test\input_empty.txt test\out_empty.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_good_empty.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM input, в котором нечего заменять
REM пустой файл
expand_template.exe test\input_empty.txt test\out_empty.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_empty.txt test\correct_out_empty.txt
IF ERRORLEVEL 1 GOTO err

REM файл с переводом строки
expand_template.exe test\input_newline.txt test\out_newline.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_newline.txt test\correct_out_newline.txt
IF ERRORLEVEL 1 GOTO err

REM файл не содержащий искомых слов
expand_template.exe test\input_noparams.txt test\out_noparams.txt word horde
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_noparams.txt test\correct_out_noparams.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM пустые строки
REM замена пустой строки (просто копирование)
expand_template.exe test\input_copy.txt test\out_copy.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_copy.txt test\correct_out_copy.txt
IF ERRORLEVEL 1 GOTO err

REM замена на пустую строку (удаление искомой строки)
expand_template.exe test\input_nullvalue.txt test\out_nullvalue.txt ЛИШНЕЕ ""
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_nullvalue.txt test\correct_out_nullvalue.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM замена
REM замена слова
expand_template.exe test\input_word.txt test\out_word.txt "СЛОВО" "Ничего не"
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_word.txt test\correct_out_word.txt
IF ERRORLEVEL 1 GOTO err

REM замена части слова
expand_template.exe test\input_wordpart.txt test\out_wordpart.txt ница ь
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_wordpart.txt test\correct_out_wordpart.txt
IF ERRORLEVEL 1 GOTO err

REM несколько одинаковых замен
expand_template.exe test\input_samewords.txt test\out_samewords.txt 1 2
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_samewords.txt test\correct_out_samewords.txt
IF ERRORLEVEL 1 GOTO err

REM несколько параметров
expand_template.exe test\input_severalparams.txt test\out_severalparams.txt Знак Число решётка рвет окна крошки дом клон
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_severalparams.txt test\correct_out_severalparams.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit