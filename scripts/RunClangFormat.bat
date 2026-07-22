@echo off
setlocal EnableDelayedExpansion

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo.
echo =====================================
echo Running clang-format
echo =====================================
echo.

set FILE_COUNT=0
set FORMATTED_COUNT=0

for /f "tokens=*" %%F in ('git diff --cached --name-only --diff-filter=ACMR') do (

    set "EXT=%%~xF"

    if /I "!EXT!"==".cpp" call :FormatFile "%%F"
    if /I "!EXT!"==".cc"  call :FormatFile "%%F"
    if /I "!EXT!"==".cxx" call :FormatFile "%%F"
    if /I "!EXT!"==".h"   call :FormatFile "%%F"
    if /I "!EXT!"==".hpp" call :FormatFile "%%F"
)

if "%FILE_COUNT%"=="0" (
    echo No staged C++ files found. Nothing to format.
    goto :Cleanup
)

if "%FORMATTED_COUNT%" NEQ "0" (
    echo.
    echo =====================================
    echo WARNING: Files were reformatted.
    echo Please review and stage the changes.
    echo =====================================

    set EXIT_CODE=1
    goto :Cleanup
)

echo.
echo =====================================
echo clang-format passed.
echo Checked %FILE_COUNT% file(s).
echo =====================================

set EXIT_CODE=0
goto :Cleanup


:FormatFile

set /a FILE_COUNT+=1

echo Formatting:
echo   %~1

clang-format -i "%~1"

if errorlevel 1 (
    echo.
    echo ERROR formatting:
    echo   %~1
    set EXIT_CODE=1
    goto :Cleanup
)

REM Check whether clang-format changed the file
git diff -- "%~1" >nul

if not errorlevel 1 (
    set /a FORMATTED_COUNT+=1
    echo Modified:
    echo   %~1
)

echo.

exit /b 0


:Cleanup

popd

if "%1" NEQ "nopause" pause

exit /b %EXIT_CODE%
