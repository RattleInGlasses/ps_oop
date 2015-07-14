REM ���⮩ �室��� ��⮪
type test\empty.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\empty.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ �� ��ॢ��� ��ப�
type test\newline.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_newline.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ �� ������ ᨬ����
type test\1sym.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_1sym.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ ��� ��譨� �஡����
type test\no_extra_spaces.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_no_extra_spaces.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ c ��譨�� �஡�����
type test\strings_with_extra_spaces.txt | remspaces.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_strings_with_extra_spaces.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit