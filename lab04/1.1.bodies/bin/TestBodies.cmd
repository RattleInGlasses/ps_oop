REM проверка обработки неверного ввода
type test\input_badInput.txt | bodies > test\stdout
FC /B test\stdout test\output_badInput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM пустой список тел
type test\input_zeroBodiesCount.txt | bodies > test\stdout
FC /B test\stdout test\output_zeroBodiesCount.txt
IF ERRORLEVEL 1 GOTO err

REM одно тело
type test\input_oneBody.txt | bodies > test\stdout
FC /B test\stdout test\output_oneBody.txt
IF ERRORLEVEL 1 GOTO err

REM два тела
type test\input_twoBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_twoBodies.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM проверка создания всех простых тел с отрицательными параметрами
type test\input_allNegativeSolidBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allNegativeSolidBodies.txt
IF ERRORLEVEL 1 GOTO err

REM проверка создания всех простых тел с нулевыми параметрами
type test\input_allZeroSolidBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allZeroSolidBodies.txt
IF ERRORLEVEL 1 GOTO err

REM проверка создания всех тел с положительными параметрами
REM // все простые, сложное <- (все простые и сложное)
type test\input_allBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allBodies.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM проверка нахождения тела с наибольшей массой и тела, наиболее лёгкого в воде
REM масса1 <, весвводе1 >
REM par 5000 1 1 1 - par 2000 3 1 1
type test\input_1.txt | bodies > test\stdout
FC /B test\stdout test\output_1.txt
IF ERRORLEVEL 1 GOTO err

REM масса1 <, весвводе1 <
REM par 2000 1 1 1 - par 4000 1 1 1
type test\input_2.txt | bodies > test\stdout
FC /B test\stdout test\output_2.txt
IF ERRORLEVEL 1 GOTO err

REM масса1 >, весвводе1 >
REM par 4000 1 1 1 - par 2000 1 1 1
type test\input_3.txt | bodies > test\stdout
FC /B test\stdout test\output_3.txt
IF ERRORLEVEL 1 GOTO err

REM масса1 >, весвводе1 <
REM par 2000 3 1 1 - par 5000 1 1 1
type test\input_4.txt | bodies > test\stdout
FC /B test\stdout test\output_4.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM удачное завершение
color 2
echo Тестирование завершилось без ошибок
goto exit

:err
color 4
echo Обнаружена ошибка

:exit