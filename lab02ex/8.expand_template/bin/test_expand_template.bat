REM �����४�� ��ࠬ����
REM ++++++++++++++++++++++++++++
REM ������⢮ ��㬥�⮢
REM ��� ��㬥�⮢
expand_template.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM �������筮 ��㬥�⮢
expand_template.exe input > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_1param.txt
IF ERRORLEVEL 1 GOTO err

REM ����⭮� ������⢮ ��㬥�⮢
expand_template.exe input output param > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_oddparams.txt
IF ERRORLEVEL 1 GOTO err

expand_template.exe input output param1 value1 param2 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_oddparams.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �訡�� ������ 䠩���
REM �� ���뢠�� input
expand_template.exe test\nosuchfile.txt test\output.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM �� ���뢠�� output
expand_template.exe test\input_empty.txt "D:/:\D\out.txt" > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ����� ��ப�
REM ������ ���⮩ ��ப� (���� ����஢����)
expand_template.exe test\input_copy.txt test\out_copy.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_copy.txt test\correct_out_copy.txt
IF ERRORLEVEL 1 GOTO err

REM ������ �� ������ ��ப� (㤠����� �᪮��� ��ப�)
expand_template.exe test\input_nullvalue.txt test\out_nullvalue.txt ������ ""
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_nullvalue.txt test\correct_out_nullvalue.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �뢮� ᮮ�饭�� �� �ᯥ譮� �����襭��
expand_template.exe test\input_empty.txt test\out_empty.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_good_empty.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM input, � ���஬ ��祣� ��������
REM ���⮩ 䠩�
expand_template.exe test\input_empty.txt test\out_empty.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_empty.txt test\correct_out_empty.txt
IF ERRORLEVEL 1 GOTO err

REM 䠩� � ��ॢ���� ��ப�
expand_template.exe test\input_newline.txt test\out_newline.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_newline.txt test\correct_out_newline.txt
IF ERRORLEVEL 1 GOTO err

REM 䠩� �� ᮤ�ঠ騩 �᪮��� ᫮�
expand_template.exe test\input_noparams.txt test\out_noparams.txt word horde
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_noparams.txt test\correct_out_noparams.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ����� ��ப�
REM ������ ���⮩ ��ப� (���� ����஢����)
expand_template.exe test\input_copy.txt test\out_copy.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_copy.txt test\correct_out_copy.txt
IF ERRORLEVEL 1 GOTO err

REM ������ �� ������ ��ப� (㤠����� �᪮��� ��ப�)
expand_template.exe test\input_nullvalue.txt test\out_nullvalue.txt ������ ""
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_nullvalue.txt test\correct_out_nullvalue.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ������
REM ������ ᫮��
expand_template.exe test\input_word.txt test\out_word.txt "�����" "��祣� ��"
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_word.txt test\correct_out_word.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ��� ᫮��
expand_template.exe test\input_wordpart.txt test\out_wordpart.txt ��� �
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_wordpart.txt test\correct_out_wordpart.txt
IF ERRORLEVEL 1 GOTO err

REM ��᪮�쪮 ���������� �����
expand_template.exe test\input_samewords.txt test\out_samewords.txt 1 2
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_samewords.txt test\correct_out_samewords.txt
IF ERRORLEVEL 1 GOTO err

REM ��᪮�쪮 ��ࠬ��஢
expand_template.exe test\input_severalparams.txt test\out_severalparams.txt ���� ��᫮ ���⪠ ࢥ� ���� ��誨 ��� ����
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_severalparams.txt test\correct_out_severalparams.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit