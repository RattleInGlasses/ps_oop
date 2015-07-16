REM некорректные параметры
REM без аргументов
translator.exe > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM слишком много аргументов
translator.exe 1 2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2args.txt
IF ERRORLEVEL 1 GOTO err

REM ошибка открытия файла
translator.exe 1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM проверка сохранения нового слова в оперативной памяти
copy test\testVocabulary.txt vocabulary.txt
type test\input_saveWordCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_saveWordCheck.txt
IF ERRORLEVEL 1 GOTO err

REM проверка сохранения нового слова в долговременной памяти
type test\input_savedWordCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_savedWordCheck.txt
IF ERRORLEVEL 1 GOTO err

REM проверка отказа от сохранения слова в оперативной памяти
copy test\testVocabulary.txt vocabulary.txt
type test\input_noRamSaveWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noRamSaveWord.txt
IF ERRORLEVEL 1 GOTO err

REM проверка отказа от сохранения слова в долговременной памяти
copy test\testVocabulary.txt vocabulary.txt
type test\input_noStorageSaveWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noStorageSaveWord.txt
IF ERRORLEVEL 1 GOTO err
type test\input_noStorageSavedWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noStorageSavedWord.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM проверка перевода и распознования разного регистра при переводе
copy test\testVocabulary.txt vocabulary.txt
type test\input_translationCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_translationCheck.txt
IF ERRORLEVEL 1 GOTO err

REM проверка сохранения в верхнем регистре
copy test\testVocabulary.txt vocabulary.txt
type test\input_saveCaseCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_saveCaseCheck.txt
IF ERRORLEVEL 1 GOTO err
type test\input_savedCaseCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_savedCaseCheck.txt
IF ERRORLEVEL 1 GOTO err

REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit