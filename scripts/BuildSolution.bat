@echo off

REM This script builds the Unreal solution using MSBuild. It requires that the project has been set up and that a solution file exists in the repository root.

setlocal EnableDelayedExpansion

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

echo.
echo ==========================================
echo Building Unreal Solution
echo ==========================================
echo.

REM ------------------------------------------
REM Find solution file
REM ------------------------------------------

set SOLUTION=

for %%F in (*.sln) do (
    if defined SOLUTION (
        echo ERROR: Multiple solution files found.
        popd
        pause
        exit /b 1
    )

    set SOLUTION=%%F
)

if not defined SOLUTION (
    echo ERROR: No solution file found.
    echo Run SetupProject.bat first.
    popd
    pause
    exit /b 1
)

echo Solution:
echo     %SOLUTION%
echo.


REM ------------------------------------------
REM Select build configuration
REM ------------------------------------------

echo Select build configuration:
echo.
echo 1. Development Editor
echo 2. DebugGame Editor
echo 3. Development
echo 4. DebugGame
echo 5. Shipping
echo.

choice /C 12345 /M "Select configuration"

if errorlevel 5 set CONFIG=Shipping
if errorlevel 4 set CONFIG=DebugGame
if errorlevel 3 set CONFIG=Development
if errorlevel 2 set CONFIG=DebugGame Editor
if errorlevel 1 set CONFIG=Development Editor

echo.
echo Selected:
echo     %CONFIG%
echo.


REM ------------------------------------------
REM Locate MSBuild
REM ------------------------------------------

echo Searching for MSBuild...

set "MSBUILD="

REM Use Visual Studio locator if available
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    for /f "usebackq delims=" %%A in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
        if not defined MSBUILD set "MSBUILD=%%A"
    )
)

if not defined MSBUILD (
    echo.
    echo ERROR: MSBuild was not found.
    echo Install Visual Studio with:
    echo   - Desktop development with C++
    echo   - Game development with C++
    popd
    pause
    exit /b 1
)

echo MSBuild:
echo     %MSBUILD%
echo.


REM ------------------------------------------
REM Build
REM ------------------------------------------

echo Restoring NuGet packages...

"%MSBUILD%" "%SOLUTION%" ^
    /t:Restore ^
    /m

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: NuGet restore failed.
    popd
    pause
    exit /b 1
)

echo.
echo Starting build...

"%MSBUILD%" "%SOLUTION%" ^
    /m ^
    /p:Configuration="%CONFIG%" ^
    /p:Platform=Win64

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed.
    popd
    pause
    exit /b 1
)

echo.
echo ==========================================
echo Build complete.
echo ==========================================

popd
if "%~1" NEQ "nopause" pause