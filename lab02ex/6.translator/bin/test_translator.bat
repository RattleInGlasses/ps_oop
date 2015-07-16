REM �����४�� ��ࠬ����
REM ��� ��㬥�⮢
translator.exe > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM ᫨誮� ����� ��㬥�⮢
translator.exe 1 2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2args.txt
IF ERRORLEVEL 1 GOTO err

REM �訡�� ������ 䠩��
translator.exe 1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM �஢�ઠ ��࠭���� ������ ᫮�� � ����⨢��� �����
copy test\testVocabulary.txt vocabulary.txt
type test\input_saveWordCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_saveWordCheck.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ ��࠭���� ������ ᫮�� � ������६����� �����
type test\input_savedWordCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_savedWordCheck.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ �⪠�� �� ��࠭���� ᫮�� � ����⨢��� �����
copy test\testVocabulary.txt vocabulary.txt
type test\input_noRamSaveWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noRamSaveWord.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ �⪠�� �� ��࠭���� ᫮�� � ������६����� �����
copy test\testVocabulary.txt vocabulary.txt
type test\input_noStorageSaveWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noStorageSaveWord.txt
IF ERRORLEVEL 1 GOTO err
type test\input_noStorageSavedWord.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_noStorageSavedWord.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM �஢�ઠ ��ॢ��� � �ᯮ�������� ࠧ���� ॣ���� �� ��ॢ���
copy test\testVocabulary.txt vocabulary.txt
type test\input_translationCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_translationCheck.txt
IF ERRORLEVEL 1 GOTO err

REM �஢�ઠ ��࠭���� � ���孥� ॣ����
copy test\testVocabulary.txt vocabulary.txt
type test\input_saveCaseCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_saveCaseCheck.txt
IF ERRORLEVEL 1 GOTO err
type test\input_savedCaseCheck.txt | translator.exe vocabulary.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_savedCaseCheck.txt
IF ERRORLEVEL 1 GOTO err

REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit