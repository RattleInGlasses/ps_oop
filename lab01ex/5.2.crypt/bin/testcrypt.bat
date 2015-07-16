REM ��ࠬ����
REM ����� ��� ��ࠬ��஢
crypt.exe > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � 2-�� ��ࠬ��ࠬ�
crypt.exe decrypt input_empty.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_2args.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � 5-�. ��ࠬ��ࠬ�
crypt.exe decrypt input_empty.txt encrypted.txt 213 smthelse > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_5args.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ����� � ������ ��ࠬ��஬
REM ����୮� �������
crypt.exe doit! input_empty.txt encrypted.txt 213 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_wrongTaskArg.txt
IF ERRORLEVEL 1 GOTO err


REM ���ࠢ���� ����
REM ���� - �� �᫮
REM ���� ᨬ���� �� �᫮��
crypt.exe encrypt input_empty.txt encrypted.txt �����(200) > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err

REM ���᫮�� ᨬ���� ��᫥ ���
crypt.exe encrypt input_empty.txt encrypted.txt 200(�����) > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err

REM �� 楫�� �᫮
crypt.exe encrypt input_empty.txt encrypted.txt 2.00 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keynotint.txt
IF ERRORLEVEL 1 GOTO err


REM ���� < 0
crypt.exe encrypt input_empty.txt encrypted.txt -131 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keyless0.txt
IF ERRORLEVEL 1 GOTO err

REM ���� > 255
crypt.exe encrypt input_empty.txt encrypted.txt 256 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_keymore255.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �訡�� ������ 䠩���
REM �� ���뢠�� input
crypt.exe encrypt test\nosuchfile.txt test\encrypted.txt 250 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM �� ���뢠�� output
crypt.exe encrypt test\input_empty.txt DXD:\somefile.txt 250 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ��஢���� � ����஢����
REM ���⮩ 䠩�
crypt.exe encrypt test\input_empty.txt test\encrypted_empty.txt 250 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_empty.txt test\decrypted_empty.txt 250 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_empty.txt test\decrypted_empty.txt
IF ERRORLEVEL 1 GOTO err


REM 䠩� � ����� ᨬ�����
crypt.exe encrypt test\input_1byte.txt test\encrypted_1byte.txt 163 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_1byte.txt test\decrypted_1byte.txt 163 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_1byte.txt test\decrypted_1byte.txt
IF ERRORLEVEL 1 GOTO err


REM 䠩� � ��᪮�쪨�� ᨬ������
crypt.exe encrypt test\input_manybytes.txt test\encrypted_manybytes.txt 27 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_encryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

crypt.exe decrypt test\encrypted_manybytes.txt test\decrypted_manybytes.txt 27 > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_decryptgoodend.txt
IF ERRORLEVEL 1 GOTO err

FC /B test\input_manybytes.txt test\decrypted_manybytes.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit