@echo off

REM This script cleans the Unreal project by resetting it and setting it up again. See ResetProject.bat and SetupProject.bat for details. 

setlocal

set SCRIPT_DIR=%~dp0

echo.
echo ==========================================
echo Cleaning Unreal Project
echo ==========================================
echo.

call "%SCRIPT_DIR%ResetProject.bat" nopause


if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Project reset failed.
    pause
    exit /b 1
)

echo.
echo.

call "%SCRIPT_DIR%SetupProject.bat" nopause

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Project setup failed.
    pause
    exit /b 1
)

echo.
echo ==========================================
echo Project Cleaning Complete.
echo ==========================================

if "%~1" NEQ "nopause" pause