REM �����४�� ��ࠬ����
REM ++++++++++++++++++++++++++++
REM ������⢮ ��㬥�⮢
REM ��� ��㬥�⮢
sets.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM ᫨誮� ����� ��㬥�⮢
sets.exe 1 2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2params.txt
IF ERRORLEVEL 1 GOTO err


REM ᮤ�ঠ��� ��㬥��
REM ��㬥�� �� �᫮
sets.exe twenty > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notint.txt
IF ERRORLEVEL 1 GOTO err

REM ��㬥�� �� 楫�� �᫮
sets.exe 1.1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notint.txt
IF ERRORLEVEL 1 GOTO err

REM ��㬥�� < 1
sets.exe 0 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_notpositive.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ���४⭠� ࠡ��
sets.exe 5 > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\5.txt
IF ERRORLEVEL 1 GOTO err

sets.exe 100 > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\100.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit