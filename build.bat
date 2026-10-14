@echo off
setlocal
pushd "%~dp0"
if errorlevel 1 exit /b 1

if exist ".tools\w64devkit\bin\gcc.exe" set "PATH=%~dp0.tools\w64devkit\bin;%PATH%"
if exist ".tools\cmake-3.31.12-windows-x86_64\bin\cmake.exe" set "PATH=%~dp0.tools\cmake-3.31.12-windows-x86_64\bin;%PATH%"

set "GAME_CMAKE="
for /f "delims=" %%I in ('where cmake.exe 2^>nul') do if not defined GAME_CMAKE set "GAME_CMAKE=%%I"
if defined GAME_CMAKE goto configure

set "GAME_VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%GAME_VSWHERE%" goto missing_cmake
for /f "usebackq delims=" %%I in (`"%GAME_VSWHERE%" -latest -products * -find Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`) do set "GAME_CMAKE=%%I"
if not defined GAME_CMAKE goto missing_cmake

:configure
set "RAYLIB_OPTION="
if exist ".tools\raylib-5.5\CMakeLists.txt" set "RAYLIB_OPTION=-DFETCHCONTENT_SOURCE_DIR_RAYLIB=%~dp0.tools\raylib-5.5"
"%GAME_CMAKE%" -S . -B build -DGAME_DEBUG=ON %RAYLIB_OPTION%
if errorlevel 1 goto failed
"%GAME_CMAKE%" --build build --config Debug -j 8
if errorlevel 1 goto failed
if /i "%~1"=="--build-only" (
    popd
    endlocal
    exit /b 0
)

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
