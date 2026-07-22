@echo off
setlocal EnableDelayedExpansion

set SCRIPT_DIR=%~dp0
pushd "%SCRIPT_DIR%\.."

set TARGET_NAME=%~1
set CONFIG=%~2


echo.
echo ==========================================
echo Generating clang compilation database
echo ==========================================
echo.

REM --------------------------------------------------
REM Find uproject
REM --------------------------------------------------

set UPROJECT=

for %%F in (*.uproject) do (
    set UPROJECT=%%F
    goto found_uproject
)

:found_uproject

if "%UPROJECT%"=="" (
    echo ERROR: No .uproject file found.
    popd
    exit /b 1
)

echo Found project:
echo   %UPROJECT%
echo.

REM Extract project name
for %%F in ("%UPROJECT%") do (
    set PROJECT_NAME=%%~nF
)

REM --------------------------------------------------
REM Find Unreal Engine version
REM --------------------------------------------------

set ENGINE_VERSION=

for /f "tokens=2 delims=:" %%A in ('findstr /i "EngineAssociation" "%UPROJECT%"') do (
    set ENGINE_VERSION=%%A
)

REM Cleanup JSON formatting
set ENGINE_VERSION=%ENGINE_VERSION:"=%
set ENGINE_VERSION=%ENGINE_VERSION:,=%
set ENGINE_VERSION=%ENGINE_VERSION: =%

if "%ENGINE_VERSION%"=="" (
    echo ERROR: Could not determine Unreal Engine version.
    popd
    exit /b 1
)

echo Unreal Engine version:
echo   %ENGINE_VERSION%
echo.

REM --------------------------------------------------
REM Locate UnrealBuildTool
REM --------------------------------------------------

set UBT_PATH=C:\Program Files\Epic Games\UE_%ENGINE_VERSION%\Engine\Binaries\DotNET\UnrealBuildTool

if not exist "%UBT_PATH%\UnrealBuildTool.exe" (
    echo ERROR: UnrealBuildTool not found:
    echo   %UBT_PATH%
    popd
    exit /b 1
)

echo Using UnrealBuildTool:
echo   %UBT_PATH%\UnrealBuildTool.exe
echo.


REM --------------------------------------------------
REM Find Unreal targets
REM --------------------------------------------------

set TARGET_COUNT=0

for %%F in (Source\*.Target.cs) do (
    set /a TARGET_COUNT+=1

    set TARGET_NAME=%%~nF
    set TARGET_NAME=!TARGET_NAME:.Target=!

    set TARGET_!TARGET_COUNT!=!TARGET_NAME!
)

if %TARGET_COUNT%==0 (
    echo ERROR: No Unreal targets found.
    echo Expected files:
    echo   Source\*.Target.cs
    popd
    exit /b 1
)

echo Available targets:
echo.

for /l %%I in (1,1,%TARGET_COUNT%) do (
    echo %%I^) !TARGET_%%I!
)

if "%TARGET_NAME%"=="" (

    echo Recommended: Editor
    echo.

    set /p TARGET_SELECTION="Select target number: "

    set TARGET_NAME=!TARGET_%TARGET_SELECTION%!

    if "!TARGET_NAME!"=="" (
        echo ERROR: Invalid target selection.
        popd
        exit /b 1
    )

	echo.
	echo Selected target:
	echo   %TARGET_NAME%
	echo.

) else (

    echo Using target from command line:
    echo   %TARGET_NAME%
)


REM --------------------------------------------------
REM Select configuration
REM --------------------------------------------------

echo Available configurations:
echo.
echo 1^) Development
echo 2^) DebugGame
echo 3^) Shipping
echo.

if "%CONFIG%"=="" (

    echo Recommended: Development
    echo.

    set /p CONFIG_SELECTION="Select configuration number: "

    if "%CONFIG_SELECTION%"=="1" set CONFIG=Development
    if "%CONFIG_SELECTION%"=="2" set CONFIG=DebugGame
    if "%CONFIG_SELECTION%"=="3" set CONFIG=Shipping

    if "%CONFIG%"=="" (
        echo ERROR: Invalid configuration selection.
        popd
        exit /b 1
    )

	echo.
	echo Selected configuration:
	echo   %CONFIG%
	echo.

) else (

    echo Using configuration from command line:
    echo   %CONFIG%
)


REM --------------------------------------------------
REM Generate database
REM --------------------------------------------------

echo Generating compile_commands.json...
echo.

"%UBT_PATH%\UnrealBuildTool.exe" ^
    %TARGET_NAME% ^
    Win64 ^
    %CONFIG% ^
    -Project="%CD%\%UPROJECT%" ^
    -OutputDir="%CD%" ^
    -Mode=GenerateClangDatabase

if errorlevel 1 (
    echo.
    echo ERROR: Failed to generate clang database.
    popd
    exit /b 1
)


REM --------------------------------------------------
REM Verify result
REM --------------------------------------------------

if not exist "compile_commands.json" (
    echo.
    echo ERROR: UnrealBuildTool completed but compile_commands.json was not created.
    popd
    exit /b 1
)

echo.
echo ==========================================
echo clang database generated successfully
echo ==========================================
echo.

popd

if "%1" NEQ "nopause" pause
exit /b 0
