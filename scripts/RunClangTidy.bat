@echo off
setlocal EnableDelayedExpansion

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

set FILE_COUNT=0
set FAILED=0
set EXIT_CODE=0

echo Running clang-tidy...
echo.

if not exist "compile_commands.json" (
    echo compile_commands.json not found.
    echo Generating clang database...
    echo.

	call "%SCRIPT_DIR%GenerateClangDatabase.bat" "%~1" "%~2" nopause

    if errorlevel 1 (
        echo.
        echo ERROR: Failed to generate compile_commands.json.
        set EXIT_CODE=1
        goto :Cleanup
    )
)

if not exist "compile_commands.json" (
    echo.
    echo ERROR: compile_commands.json still not found after generation.
    set EXIT_CODE=1
    goto :Cleanup
)

echo Using:
echo   compile_commands.json
echo.

echo Staged files:
git diff --cached --name-only
echo.

for /f "tokens=*" %%F in ('git diff --cached --name-only --diff-filter=ACMR') do (

    set "EXT=%%~xF"

    if /I "!EXT!"==".cpp" call :RunTidy "%%F"
    if /I "!EXT!"==".cc" call :RunTidy "%%F"
    if /I "!EXT!"==".cxx" call :RunTidy "%%F"
    if /I "!EXT!"==".h" call :RunTidy "%%F"
    if /I "!EXT!"==".hpp" call :RunTidy "%%F"
)

if "%FILE_COUNT%"=="0" (
    echo.
    echo No staged C++ files found. Nothing to check.
    goto :Cleanup
)

if "%FAILED%"=="1" (
    echo.
    echo =====================================
    echo clang-tidy found issues.
    echo =====================================

    set EXIT_CODE=1
    goto :Cleanup
)

echo.
echo =====================================
echo clang-tidy passed.
echo Checked %FILE_COUNT% file(s).
echo =====================================

goto :Cleanup


:RunTidy

set /a FILE_COUNT+=1

echo.
echo =====================================
echo Checking %~1...
echo =====================================
echo.

clang-tidy -p . "%~1" --extra-arg=-Wno-unused-command-line-argument

if errorlevel 1 (
    echo.
	echo FAILED: %~1
    set FAILED=1
)

exit /b 0


:Cleanup

popd

if "%1" NEQ "nopause" pause

exit /b %EXIT_CODE%
