@echo off

REM This script resets the Unreal project by removing generated files and directories.

setlocal

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo.
echo ==========================================
echo Resetting Unreal Project
echo ==========================================
echo.

if exist "Binaries" (
    echo Removing Binaries...
    rmdir /S /Q "Binaries"
)

if exist "Intermediate" (
    echo Removing Intermediate...
    rmdir /S /Q "Intermediate"
)

if exist "Saved" (
    echo Removing Saved...
    rmdir /S /Q "Saved"
)

for %%F in (*.sln) do (
    echo Removing %%F...
    del /Q "%%F"
)

if exist "compile_commands.json" (
    echo Removing compile_commands.json...
    del /Q "compile_commands.json"
)

echo.
echo Project reset complete.

popd
if "%~1" NEQ "nopause" pause
