REM �訡�� �� ������� ������ 
type test\input_errors.txt | findmaxex > test\stdout
FC /B test\stdout test\output_errors.txt
IF ERRORLEVEL 1 GOTO err

REM ���⮩ ᯨ᮪
type test\input_emptylist.txt | findmaxex > test\stdout 
FC /B test\stdout test\output_emptylist.txt
IF ERRORLEVEL 1 GOTO err

REM ���� ������
type test\input_1entry.txt | findmaxex > test\stdout
FC /B test\stdout test\output_1entry.txt
IF ERRORLEVEL 1 GOTO err

REM ��� �����
type test\input_2entries.txt | findmaxex > test\stdout
FC /B test\stdout test\output_2entries.txt
IF ERRORLEVEL 1 GOTO err

REM �� �����
type test\input_3entries.txt | findmaxex > test\stdout
FC /B test\stdout test\output_3entries.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit