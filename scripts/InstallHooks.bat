@echo off
setlocal

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo Installing Git hooks...
echo.
echo.

if not exist ".git" (
    echo ERROR: This is not a Git repository.
    popd
    pause
    exit /b 1
)

set HOOKS=pre-commit

for %%H in (%HOOKS%) do (

    if exist ".git\hooks\%%H" (
        echo Updating %%H...
    ) else (
        echo Installing %%H...
    )

    copy /Y "scripts\%%H" ".git\hooks\%%H" >nul
)

echo.
echo Git hooks are installed.

echo.
echo.

popd
if "%1" NEQ "nopause" pause