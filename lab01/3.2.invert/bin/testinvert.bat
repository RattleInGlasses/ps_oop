REM �����४�� ��ࠬ����
REM ++++++++++++++++++++++++++++
REM ������⢮ ��㬥�⮢
REM ��� ��㬥�⮢
invert > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output noparam.txt
IF ERRORLEVEL 1 GOTO err

REM ᫨誮� ����� ��㬥�⮢
invert 1 2 > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output 2param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM ᮤ�ঠ��� ��㬥��
REM ���������� ������ 䠩�
invert nosuchfile.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output cantopen.txt
IF ERRORLEVEL 1 GOTO err

REM �����४�� 䠩�
REM ���⮩ 䠩�
invert empty.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM ᮤ�ন� �� ⮫쪮 �᫠
REM ����஢�� ᨬ��� � ��砫� �᫠
invert brokenmatrix1.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM ����஢�� ᨬ��� � �।��� �᫠
invert brokenmatrix2.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM ����஢�� ᨬ��� ��᫥ �᫠
invert brokenmatrix3.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err

REM ���ࠢ���� ࠧ��� ������
invert wrongmatrix.txt > output
IF NOT ERRORLEVEL 1 GOTO err
FC /B output brokenfile.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �஢�ઠ �ࠢ��쭮�� �믮������ �८�ࠧ������
invert matrix1.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted1.txt
IF ERRORLEVEL 1 GOTO err

invert matrix2.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted2.txt
IF ERRORLEVEL 1 GOTO err

invert matrix3.txt > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output inverted3.txt
IF ERRORLEVEL 1 GOTO err

invert "martrix4 (notInvertable).txt" > output
IF NOT ERRORLEVEL 0 GOTO err
FC /B output cantinvert.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit