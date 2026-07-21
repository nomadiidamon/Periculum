@echo off
REM This script checks for the presence of a Git repository, installs Git hooks, locates the Unreal project file, finds the Unreal Version Selector, and generates Visual Studio project files.

setlocal

REM ==========================================
REM Unreal Project Setup Script
REM ==========================================

set SCRIPT_DIR=%~dp0

REM Move to repository root
pushd "%SCRIPT_DIR%\.."

echo.
echo ==========================================
echo Setting Up Unreal Project
echo ==========================================
echo.

REM ------------------------------------------
REM Verify Git repository
REM ------------------------------------------

if not exist ".git" (
    echo ERROR: This does not appear to be a Git repository.
    echo Run this script from within a Git repository.
    popd
    pause
    exit /b 1
)

echo.
echo.

REM ------------------------------------------
REM Install Git hooks
REM ------------------------------------------

call "%SCRIPT_DIR%InstallHooks.bat" nopause
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to install Git hooks.
    popd
    pause
    exit /b 1
)

echo.
echo.

REM ------------------------------------------
REM Find Unreal project file
REM ------------------------------------------

echo Searching for Unreal project file...

set UPROJECT=

for %%F in (*.uproject) do (
    if defined UPROJECT (
        echo ERROR: Multiple .uproject files found.
        echo Please keep only one project in the repository root.
        popd
        pause
        exit /b 1
    )

    set UPROJECT=%%F
)

if not defined UPROJECT (
    echo ERROR: No .uproject file found in repository root.
    popd
    pause
    exit /b 1
)

echo Found project:
echo     %UPROJECT%
echo.
echo.


REM ------------------------------------------
REM Locate Unreal Version Selector
REM ------------------------------------------

echo Searching for Unreal Version Selector...

set "UVS="

REM Check 64-bit Program Files
if exist "%ProgramFiles%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" (
    set "UVS=%ProgramFiles%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"
)

REM Check 32-bit Program Files
if not defined UVS if exist "%ProgramFiles(x86)%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" (
    set "UVS=%ProgramFiles(x86)%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"
)

REM Fallback search
if not defined UVS (
    for /r "%ProgramFiles%\Epic Games" %%F in (UnrealVersionSelector.exe) do (
        if not defined UVS set "UVS=%%~F"
    )
)

if not defined UVS (
    echo.
    echo ERROR: Unreal Version Selector was not found.
    echo Install Unreal Engine through Epic Games Launcher.
    popd
    pause
    exit /b 1
)

echo Found:
echo     %UVS%
echo.
echo.


REM ------------------------------------------
REM Generate Visual Studio project files
REM ------------------------------------------

echo Generating Visual Studio project files...


call "%UVS%" /projectfiles "%CD%\%UPROJECT%"

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Failed to generate project files.
    popd
    pause
    exit /b 1
)

echo.
echo ==========================================
echo Unreal project setup complete.
echo ==========================================

popd
if "%1" NEQ "nopause" pause