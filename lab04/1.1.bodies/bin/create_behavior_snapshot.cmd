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
type test\input_badInput.txt | bodies > test\output_badInput.txt
type test\input_zeroBodiesCount.txt | bodies > test\output_zeroBodiesCount.txt
type test\input_oneBody.txt | bodies > test\output_oneBody.txt
type test\input_twoBodies.txt | bodies > test\output_twoBodies.txt
type test\input_allNegativeSolidBodies.txt | bodies > test\output_allNegativeSolidBodies.txt
type test\input_allZeroSolidBodies.txt | bodies > test\output_allZeroSolidBodies.txt
type test\input_allBodies.txt | bodies > test\output_allBodies.txt
type test\input_1.txt | bodies > test\output_1.txt
type test\input_2.txt | bodies > test\output_2.txt
type test\input_3.txt | bodies > test\output_3.txt
type test\input_4.txt | bodies > test\output_4.txt

:skip_rebuild