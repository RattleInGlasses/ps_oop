REM �����४�� ��ࠬ����
REM ++++++++++++++++++++++++++++
REM ������⢮ ��㬥�⮢
REM ��� ��㬥�⮢
rectangles > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_noparam.txt
IF ERRORLEVEL 1 GOTO err

REM 1 ��㬥��
rectangles 1 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_1param.txt
IF ERRORLEVEL 1 GOTO err

REM ᫨誮� ����� ��㬥�⮢
rectangles 1 2 3 4 > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_4param.txt
IF ERRORLEVEL 1 GOTO err

REM ++++++++++++++++++++++++++++
REM ᮤ�ঠ��� ��㬥��
REM ���������� ������ ���� 䠩�
rectangles nosuchfile.txt test\input11.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_cantopen1.txt
IF ERRORLEVEL 1 GOTO err

REM ���������� ������ ��ன 䠩�
rectangles test\input11.txt nosuchfile.txt > test\output
IF NOT ERRORLEVEL 1 GOTO err
FC /B test\output test\msg_cantopen2.txt
IF ERRORLEVEL 1 GOTO err


REM ==================================================================
REM �ᮡ� ��砨
REM ���⮩ 䠩�
rectangles test\input_empty.txt test\input_empty.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_empty.txt
IF ERRORLEVEL 1 GOTO err

REM 䠩� � ���⮩ ��ப��
rectangles test\input_newline.txt test\input_newline.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_empty.txt
IF ERRORLEVEL 1 GOTO err

REM �訡�� � ��ࢮ� 䠩��
rectangles test\input_error.txt test\input_newline.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_error1file.txt
IF ERRORLEVEL 1 GOTO err

REM �訡�� �� ��஬ 䠩��
rectangles test\input_newline.txt test\input_error.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic_zero_zero.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text_error1file.txt
IF ERRORLEVEL 1 GOTO err

REM ��䨪� � output
rectangles test\input11.txt test\input12.txt > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_full1.txt
IF ERRORLEVEL 1 GOTO err

REM ==================================================================
REM �஢�ઠ �ࠢ��쭮�� ��ࠡ�⪨
rectangles test\input11.txt test\input12.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic1.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text1.txt
IF ERRORLEVEL 1 GOTO err

rectangles test\input21.txt test\input22.txt test\outfile > test\output
IF ERRORLEVEL 1 GOTO err
FC /B test\outfile test\out_graphic2.txt
IF ERRORLEVEL 1 GOTO err
FC /B test\output test\out_text2.txt
IF ERRORLEVEL 1 GOTO err


REM 㤠筮� �����襭��
color 2
echo ����஢���� �����訫��� ��� �訡��
goto exit

:err
color 4
echo �����㦥�� �訡��

:exit