type test\input_normal.txt | driver.exe > test\out
IF ERRORLEVEL 1 GOTO err
FC /B test\out_normal.txt test\out
IF ERRORLEVEL 1 GOTO err

REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit