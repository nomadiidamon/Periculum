@echo off

REM This script cleans and builds the Unreal project:

REM 1.) Cleans the project by calling CleanProject.bat
REM 1.1) CleanProject.bat calls ResetProject.bat to remove generated files and directories
REM 1.2) CleanProject.bat calls SetupProject.bat to set up the project again

REM 2.) Regenerates project files by calling SetupProject.bat
REM 2.1) SetupProject.bat checks for a Git repository
REM 2.2) SetupProject.bat calls InstallHooks.bat to install Git hooks
REM 2.3) SetupProject.bat locates the Unreal project file
REM 2.4) SetupProject.bat locates the UnrealVersionSelector
REM 2.5) SetupProject.bat generates project files using UnrealVersionSelector

REM 3.) Starts the build selection by calling BuildSolution.bat
REM 3.1) BuildSolution.bat locates the solution file
REM 3.2) BuildSolution.bat prompts the user to select a build configuration
REM 3.3) BuildSolution.bat builds the solution using MSBuild

setlocal

set SCRIPT_DIR=%~dp0

echo.
echo ==========================================
echo Clean and Build Unreal Project
echo ==========================================
echo.
echo.

call "%SCRIPT_DIR%CleanProject.bat" nopause

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Cleaning failed.
    pause
    exit /b 1
)


echo.
echo.
echo.

echo Regenerating project files...
call "%SCRIPT_DIR%SetupProject.bat" nopause

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Project setup failed.
    pause
    exit /b 1
)


echo.
echo.
echo.

echo Starting build selection...
call "%SCRIPT_DIR%BuildSolution.bat" nopause

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed.
    pause
    exit /b 1
)


echo.
echo ==========================================
echo Clean build complete.
echo ==========================================

pause