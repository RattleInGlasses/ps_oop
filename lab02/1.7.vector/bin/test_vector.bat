REM 3 楫�� �᫠
type test\3int.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_3int.txt
IF ERRORLEVEL 1 GOTO err

REM 3 ����⢥���� �᫠
type test\3real.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_3real.txt
IF ERRORLEVEL 1 GOTO err

REM 6 ����⢥���� �ᥫ
type test\6real.txt | vector.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_6real.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit