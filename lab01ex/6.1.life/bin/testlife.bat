REM ��ࠬ����
REM ����� ��� ��ࠬ��஢
life.exe > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_noargs.txt
IF ERRORLEVEL 1 GOTO err

REM ����� � 3-�� ��ࠬ��ࠬ�
life.exe input.txt out.txt andonemore > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_3args.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �訡�� ������ 䠩���
REM �� ���뢠�� input
life.exe test\nosuchfile.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noinput.txt
IF ERRORLEVEL 1 GOTO err

REM �� ���뢠�� output
life.exe test\input_empty.txt 1ds:\ttt.xt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_nooutput.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �訡�� �室���� 䠩��
REM ���⮩ 䠩�
life.exe test\input_empty.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0w.txt
IF ERRORLEVEL 1 GOTO err

REM �������祭�� 䠩�
life.exe test\input_unfinished.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noend.txt
IF ERRORLEVEL 1 GOTO err

REM ���ࠢ���� ᨬ����
life.exe test\input_invalidsym.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_invalidsym.txt
IF ERRORLEVEL 1 GOTO err

REM -----------------------------------------------------
REM ࠧ��� ����
REM ᫨誮� ����讥 ����
REM ������ �ਭ�
life.exe test\input_257w.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_bigw.txt
IF ERRORLEVEL 1 GOTO err

REM �।�� �ਭ�
life.exe test\input_256w.txt test\out_256w.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\input_256w.txt test\out_256w.txt
IF ERRORLEVEL 1 GOTO err

REM ������ ����
life.exe test\input_257h.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_bigh.txt
IF ERRORLEVEL 1 GOTO err

REM �।�� �����
life.exe test\input_256h.txt test\out_256h.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\input_256h.txt test\out_256h.txt
IF ERRORLEVEL 1 GOTO err


REM ᫨誮� �����쪮� ����
REM �㫥��� �ਭ�
life.exe test\input_0w.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0w.txt
IF ERRORLEVEL 1 GOTO err

REM �㫥��� ����
life.exe test\input_0h.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_0h.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM ���ࠢ����� �뢮��
REM �뢮� � ⥪�⮢� 䠩�
life.exe test\input1.txt test\out_1.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_1.txt test\out_standard1.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM �뢮� � stdout
life.exe test\input1.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\output test\out_standard1_stdout.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �ࠢ��쭮��� ���᫥���
REM ���⮥ ����
life.exe test\input_emptyfield.txt test\out_emptyfield.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_emptyfield.txt test\out_emptyfield.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM ��ன ���
life.exe test\input2.txt test\out_2.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_2.txt test\out_standard2.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err

REM ��⨩ ���
life.exe test\input3.txt test\out_3.txt > test\output
IF NOT ERRORLEVEL 0 GOTO err
FC /B test\out_3.txt test\out_standard3.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_goodend.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit