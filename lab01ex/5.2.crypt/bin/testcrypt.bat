REM параметры
REM запуск без параметров
crypt.exe > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с 2-мя параметрами
crypt.exe decrypt input_empty.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2args.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с 5-ю. параметрами
crypt.exe decrypt input_empty.txt encrypted.txt 213 smthelse > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_5args.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM запуск с неверным параметром
REM неверное задание
crypt.exe doit! input_empty.txt encrypted.txt 213 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_wrongTaskArg.txt
IF ERRORLEVEL 1 GOTO err


REM неправильный ключ
REM ключ - не число
REM первые символы не числовые
crypt.exe encrypt input_empty.txt encrypted.txt двести(200) > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err

REM нечисловые символы после цифр
crypt.exe encrypt input_empty.txt encrypted.txt 200(двести) > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err

REM не целое число
crypt.exe encrypt input_empty.txt encrypted.txt 2.00 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err


REM ключ < 0
crypt.exe encrypt input_empty.txt encrypted.txt -131 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keyless0.txt
IF ERRORLEVEL 1 GOTO err

REM ключ > 255
crypt.exe encrypt input_empty.txt encrypted.txt 256 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keymore255.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки открытия файлов
REM не открывает input
crypt.exe encrypt test\nosuchfile.txt test\encrypted.txt 250 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM не открывает output
crypt.exe encrypt test\input_empty.txt DXD:\somefile.txt 250 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM шифрование и дешифрование
REM пустой файл
crypt.exe encrypt test\input_empty.txt test\encrypted_empty.txt 250 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_empty.txt test\decrypted_empty.txt 250 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_empty.txt test\decrypted_empty.txt
IF ERRORLEVEL 1 GOTO err


REM файл с одним символом
crypt.exe encrypt test\input_1byte.txt test\encrypted_1byte.txt 163 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_1byte.txt test\decrypted_1byte.txt 163 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_1byte.txt test\decrypted_1byte.txt
IF ERRORLEVEL 1 GOTO err


REM файл с несколькими символами
crypt.exe encrypt test\input_manybytes.txt test\encrypted_manybytes.txt 27 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_manybytes.txt test\decrypted_manybytes.txt 27 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_manybytes.txt test\decrypted_manybytes.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit