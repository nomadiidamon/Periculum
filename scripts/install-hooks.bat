@echo off
setlocal

REM Directory containing this batch file
set SCRIPT_DIR=%~dp0

REM Repository root (parent of scripts)
pushd "%SCRIPT_DIR%.."

echo Installing Git pre-commit hook...

if not exist ".git" (
    echo Error: This does not appear to be a Git repository.
    popd
    pause
    exit /b 1
)

copy /Y "%SCRIPT_DIR%pre-commit" ".git\hooks\pre-commit"

if %ERRORLEVEL% NEQ 0 (
    echo Failed to install hook.
    popd
    pause
    exit /b 1
)

echo Hook installed successfully.

popd
pause