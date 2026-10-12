@echo off
setlocal
set "PATH=C:\mingw64\bin;%PATH%"

if not exist "%~dp0build\CMakeCache.txt" (
    echo [CSOPESY] Initializing build directory and downloading dependencies...
    cmake -B "%~dp0build" -G "Ninja" -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe"
    if errorlevel 1 exit /b %errorlevel%
)

echo [CSOPESY] Compiling project...
cmake --build "%~dp0build"
if errorlevel 1 exit /b %errorlevel%

echo [CSOPESY] Build completed successfully.
exit /b 0
