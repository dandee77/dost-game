@echo off
setlocal
cd /d "%~dp0"
if exist "build\Release\SpaceAblaze.exe" (
    cd /d "%~dp0build\Release"
) else if exist "build\SpaceAblaze.exe" (
    cd /d "%~dp0build"
) else (
    echo Build the game first by running build.bat.
    exit /b 1
)
start "" /wait "SpaceAblaze.exe"
exit /b %errorlevel%
