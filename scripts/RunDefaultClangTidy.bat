@echo off
setlocal

call "%~dp0RunClangTidy.bat" PericulumEditor Development nopause

set EXIT_CODE=%ERRORLEVEL%

echo.
echo =====================================
echo Finished with exit code %EXIT_CODE%
echo =====================================
echo.

exit /b %EXIT_CODE%
