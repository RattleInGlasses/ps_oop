REM ==================================================================
REM �����४�� ��ࠬ����
REM ++++++++++++++++++++++++++++
REM ������⢮ ��㬥�⮢
REM ��� ��㬥�⮢
flipbyte > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM ᫨誮� ����� ��㬥�⮢
flipbyte 1 2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 2param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM ᮤ�ঠ��� ��㬥��
REM ����� 0
flipbyte -10 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output lesszero.txt
IF ERRORLEVEL 1 GOTO err

REM ����� 255
flipbyte 256 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output outofbyte.txt
IF ERRORLEVEL 1 GOTO err

REM ᮤ�ন� �஡��� � ⠡����
REM ---------------------
REM �஡���
flipbyte " 	 2	 " > output
IF ERRORLEVEL 1 GOTO err
FC /B output 2.txt
IF ERRORLEVEL 1 GOTO err

REM ⮫쪮 �஡���
flipbyte " 	 " > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM �� �����筮� �᫮
REM ---------------------
REM �஡��� �᫮
flipbyte 12.2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM ��稭����� �� � ����
flipbyte F1 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM ᮤ�ন� �� ���� �����
flipbyte 1F1 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err

REM ��᫥���� ᨬ��� �� ���
flipbyte 1F > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output notinteger.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �஢�ઠ �ࠢ��쭮�� �믮������ �८�ࠧ������
REM 0 -> 0
flipbyte 0 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 0.txt
IF ERRORLEVEL 1 GOTO err

REM 255 -> 255
flipbyte 255 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 255.txt
IF ERRORLEVEL 1 GOTO err

REM +25 -> 152
flipbyte +25 > output
IF ERRORLEVEL 1 GOTO err
FC /B output 25.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit