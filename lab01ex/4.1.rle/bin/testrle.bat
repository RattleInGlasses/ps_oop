REM параметры
REM запуск без параметров
rle.exe > testrle\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\output testrle\noargs.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с 2-мя параметрами
rle.exe pack input.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\2args.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с 5-ю. параметрами
rle.exe pack input.txt output.txt smthelse onemore > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\5args.txt
IF ERRORLEVEL 1 GOTO err

REM запуск с неверным параметром
rle.exe extract pack.txt unpacked.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\wrongarg.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки открытия файлов
REM не открывает input
rle.exe pack nosuchfile.txt testrle\package.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\noinput.txt
IF ERRORLEVEL 1 GOTO err

REM не открывает output
rle.exe pack testrle\empty.txt "DDD:\out.txt" > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ошибки распаковки
REM нечётная длина файла
REM файл с длиной в 1 байт
rle.exe unpack testrle\badpack1byte.txt testrle\badunpack1byte.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\wrongrleOdd.txt
IF ERRORLEVEL 1 GOTO err
IF EXIST testrle\badunpack1byte.txt GOTO err

REM файл с длиной в 3 байта
rle.exe unpack testrle\badpack3bytes.txt testrle\badunpack3bytes.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\wrongrleOdd.txt
IF ERRORLEVEL 1 GOTO err
IF EXIST testrle\badunpack3bytes.txt GOTO err

REM файл содержит 0 на месте количества
REM первый байт == 0
rle.exe unpack testrle\packFirst0.txt testrle\unpackFirst0.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\wrongrle0.txt
IF ERRORLEVEL 1 GOTO err
IF EXIST testrle\unpackFirst0.txt GOTO err

REM не первый (но нечетный) байт == 0
rle.exe unpack testrle\pack0count.txt testrle\unpack0count.txt > testrle\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B testrle\output testrle\wrongrle0.txt
IF ERRORLEVEL 1 GOTO err
IF EXIST testrle\unpack0count.txt GOTO err

REM ==================================================================
REM упаковка
REM пустой файл
rle.exe pack testrle\empty.txt testrle\emptypack.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\empty.txt testrle\emptypack.txt
IF ERRORLEVEL 1 GOTO err

REM файл с одним байтом
rle.exe pack testrle\input1byte.txt testrle\package.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\package.txt testrle\pack1byte.txt
IF ERRORLEVEL 1 GOTO err

REM файл с двумя одинаковыми байтами
rle.exe pack testrle\input2bytes.txt testrle\package.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\package.txt testrle\pack2bytes.txt
IF ERRORLEVEL 1 GOTO err

REM файл без повторяющихся байтов
rle.exe pack testrle\inputdiffbytes.txt testrle\package.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\package.txt testrle\packdiffbytes.txt
IF ERRORLEVEL 1 GOTO err

REM файл с последовательностями в 255, 256, 257 байт
rle.exe pack testrle\inputLongStreaks.txt testrle\package.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\package.txt testrle\packLongStreaks.txt
IF ERRORLEVEL 1 GOTO err

REM файл с символами №255
rle.exe pack testrle\inputSyms255.txt testrle\package.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\package.txt testrle\packSyms255.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM распаковка
REM пустой файл
rle.exe unpack testrle\emptypack.txt testrle\emptyunpacked.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\emptypack.txt testrle\emptyunpacked.txt
IF ERRORLEVEL 1 GOTO err

REM файл с одной закодированной последовательностью
rle.exe unpack testrle\pack2bytes.txt testrle\unpacked2bytes.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\input2bytes.txt testrle\unpacked2bytes.txt
IF ERRORLEVEL 1 GOTO err

REM файл с несколькими закодированными последовательностями
rle.exe unpack testrle\packdiffbytes.txt testrle\unpackedDiffBytes.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\unpackedDiffBytes.txt testrle\inputdiffbytes.txt
IF ERRORLEVEL 1 GOTO err

REM файл с последовательностями в 255, 256, 257 байт
rle.exe unpack testrle\packLongStreaks.txt testrle\unpackedLongStreaks.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\unpackedLongStreaks.txt testrle\inputLongStreaks.txt
IF ERRORLEVEL 1 GOTO err

REM файл с символами №255
rle.exe unpack testrle\packSyms255.txt testrle\unpackedSyms255.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B testrle\unpackedSyms255.txt testrle\inputSyms255.txt
IF ERRORLEVEL 1 GOTO err


REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit