REM �஢�ઠ ��ࠡ�⪨ ����୮�� �����
type test\input_badInput.txt | bodies > test\stdout
FC /B test\stdout test\output_badInput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ���⮩ ᯨ᮪ ⥫
type test\input_zeroBodiesCount.txt | bodies > test\stdout
FC /B test\stdout test\output_zeroBodiesCount.txt
IF ERRORLEVEL 1 GOTO err

REM ���� ⥫�
type test\input_oneBody.txt | bodies > test\stdout
FC /B test\stdout test\output_oneBody.txt
IF ERRORLEVEL 1 GOTO err

REM ��� ⥫�
type test\input_twoBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_twoBodies.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �஢�ઠ ᮧ����� ��� ������ ⥫ � ����⥫�묨 ��ࠬ��ࠬ�
type test\input_allNegativeSolidBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allNegativeSolidBodies.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ ᮧ����� ��� ������ ⥫ � �㫥�묨 ��ࠬ��ࠬ�
type test\input_allZeroSolidBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allZeroSolidBodies.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ ᮧ����� ��� ⥫ � ������⥫�묨 ��ࠬ��ࠬ�
REM // �� �����, ᫮���� <- (�� ����� � ᫮����)
type test\input_allBodies.txt | bodies > test\stdout
FC /B test\stdout test\output_allBodies.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �஢�ઠ ��宦����� ⥫� � �������襩 ���ᮩ � ⥫�, �������� �񣪮�� � ����
REM ����1 <, ��ᢢ���1 >
REM par 5000 1 1 1 - par 2000 3 1 1
type test\input_1.txt | bodies > test\stdout
FC /B test\stdout test\output_1.txt
IF ERRORLEVEL 1 GOTO err

REM ����1 <, ��ᢢ���1 <
REM par 2000 1 1 1 - par 4000 1 1 1
type test\input_2.txt | bodies > test\stdout
FC /B test\stdout test\output_2.txt
IF ERRORLEVEL 1 GOTO err

REM ����1 >, ��ᢢ���1 >
REM par 4000 1 1 1 - par 2000 1 1 1
type test\input_3.txt | bodies > test\stdout
FC /B test\stdout test\output_3.txt
IF ERRORLEVEL 1 GOTO err

REM ����1 >, ��ᢢ���1 <
REM par 2000 3 1 1 - par 5000 1 1 1
type test\input_4.txt | bodies > test\stdout
FC /B test\stdout test\output_4.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit