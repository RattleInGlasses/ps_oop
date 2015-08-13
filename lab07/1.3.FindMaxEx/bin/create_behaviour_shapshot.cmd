@echo off
:question
set /p rebuild=Are you shure you want to rebuild tests?(Y/N) 
IF %rebuild% == N GOTO skip_rebuild
IF %rebuild% == n GOTO skip_rebuild
IF %rebuild% == Y GOTO rebuild
IF %rebuild% == y GOTO rebuild
GOTO question

:rebuild
@echo on
type test\input_errors.txt | findmaxex > test\output_errors.txt
type test\input_emptylist.txt | findmaxex > test\output_emptylist.txt
type test\input_1entry.txt | findmaxex > test\output_1entry.txt
type test\input_2entries.txt | findmaxex > test\output_2entries.txt
type test\input_3entries.txt | findmaxex > test\output_3entries.txt

:skip_rebuild
