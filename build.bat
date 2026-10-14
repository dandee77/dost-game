@echo off
setlocal
pushd "%~dp0"
if errorlevel 1 exit /b 1

set "GAME_CMAKE="
for /f "delims=" %%I in ('where cmake.exe 2^>nul') do if not defined GAME_CMAKE set "GAME_CMAKE=%%I"
if defined GAME_CMAKE goto configure

set "GAME_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%GAME_VSWHERE%" goto missing_cmake
for /f "usebackq delims=" %%I in (`"%GAME_VSWHERE%" -latest -products * -find Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`) do set "GAME_CMAKE=%%I"
if not defined GAME_CMAKE goto missing_cmake

:configure
"%GAME_CMAKE%" -S . -B build
if errorlevel 1 goto failed
"%GAME_CMAKE%" --build build --config Debug -j 8
if errorlevel 1 goto failed

set "GAME_DIRECTORY=%CD%\build\Debug"
if not exist "%GAME_DIRECTORY%\SpaceAblaze.exe" set "GAME_DIRECTORY=%CD%\build"
if not exist "%GAME_DIRECTORY%\SpaceAblaze.exe" (
    echo Build finished but SpaceAblaze.exe was not found.
    popd
    exit /b 1
)

"%GAME_CMAKE%" -E copy_directory assets "%GAME_DIRECTORY%\assets"
if errorlevel 1 goto failed
pushd "%GAME_DIRECTORY%"
if errorlevel 1 goto failed
SpaceAblaze.exe
set "GAME_RESULT=%ERRORLEVEL%"
popd
popd
endlocal & exit /b %GAME_RESULT%

:missing_cmake
echo CMake was not found. Install CMake or the Visual Studio CMake tools.
popd
exit /b 1

:failed
set "GAME_RESULT=%ERRORLEVEL%"
echo Build failed. The game was not launched.
popd
endlocal & exit /b %GAME_RESULT%
