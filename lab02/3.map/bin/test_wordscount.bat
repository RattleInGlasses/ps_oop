REM ���⮩ �室��� ��⮪
type test\empty.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\empty.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ �� ������ ᫮��
type test\1word.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_1word.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ �� ࠧ��� ᫮�
type test\severalwords.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_severalwords.txt
IF ERRORLEVEL 1 GOTO err

REM �室��� ��⮪ �� � �������騬��� ᫮����
type test\repeated.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_repeated.txt
IF ERRORLEVEL 1 GOTO err

REM ᫮�� � ࠧ��� ॣ����
type test\wORds.txt | wordscount.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_wORds.txt
IF ERRORLEVEL 1 GOTO err



REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit