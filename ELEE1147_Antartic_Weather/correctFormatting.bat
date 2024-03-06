@echo off
setlocal enableextensions enabledelayedexpansion
:: written by Connor Philpott


title Correct C Language Formatting
echo Correct C Language Formatting
echo.

set /a i=0
set /a j=0

for %%a in (%*) do (
set /a j+=1
)

for %%b in (%*) do  (
set /a i+=1
cls
echo Correct C Language Formatting
echo.
echo Processing file !i! of %j%
echo %%b
echo.
start /wait /B .\clang-format.exe -style=file .\msvc.conf -i %%b
)

cls
echo Processed !i! of %j% files, press any key to exit.
pause