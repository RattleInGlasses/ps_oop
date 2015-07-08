REM ������⢮ ��ࠬ��஢
REM ����� ��� ��ࠬ��஢
replace > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � ����� ��ࠬ��஬
replace infile.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 1param.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � ����� ��ࠬ��ࠬ�
replace replace infile.txt outfile.txt string param5 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 5param.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ����� ��ப�
REM ����� ��ப� � ����� input
replace "" "" > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output noinput.txt
IF ERRORLEVEL 1 GOTO err

REM ����� ��ப� � ����� output
replace infile.txt "" > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output nooutput.txt
IF ERRORLEVEL 1 GOTO err

REM ����� ��ப� ����� �᪮��� ��ப�
replace infile.txt outfile.txt "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM ����� ��ப� ����� �᪮��� � �������饩 ��ப
replace infile.txt outfile.txt "" "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM ����� ��ப� ����� �������饩 ��ப�
replace infile.txt outfile.txt file "" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outNullReplaced.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM 䠩��
REM ���⮩ 䠩� ����஢����
replace empty.txt outfile.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodEmptyExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt empty.txt
IF ERRORLEVEL 1 GOTO err

REM ���⮩ 䠩� ����஢���� � ������
replace empty.txt outfile.txt file life > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodEmptyExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt empty.txt
IF ERRORLEVEL 1 GOTO err

REM � 䠩�� ��祣� ��������
replace infile.txt outfile.txt youcantfindit smth > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM ������ �� ��ப�, ���������� ��室���
replace infile.txt outfile.txt file filefile > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outWordWord.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ��ଠ�쭠� ࠡ��
REM ����� � ���� ��ࠬ��ࠬ� (����஢����)
replace infile.txt outfile.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt infile.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � �६� ��ࠬ��ࠬ� (�� ������ ��������� ��ப� - � �⮬ ��砥 �ந�室�� 㤠����� �᪮��� ��ப�)
replace infile.txt outfile.txt file
IF NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outNullReplaced.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � ���६� ��ࠬ��ࠬ� (���筠� ࠡ��)
replace infile.txt outfile.txt file life
if NOT ERRORLEVEL 0 GOTO err
FC /B output goodExit.txt
IF ERRORLEVEL 1 GOTO err
FC /B outfile.txt outReplaced.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit