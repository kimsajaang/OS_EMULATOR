================================================================================
CSOPESY Semi-Major Output 2: Desktop-Style OS Mock-up
Group 6
================================================================================

GROUP MEMBERS:
- Fabregas, Matthew M.
- Ibanez, Kane Joshua T.
- Li, Bowen
- Teoxon, Jat R.

COURSE & SECTION:
- CSOPESY

--------------------------------------------------------------------------------
1. ENTRY CLASS / MAIN FUNCTION LOCATION
--------------------------------------------------------------------------------
Entry file: src/main.cpp
Main function: int main() (Line 17 of src/main.cpp)

--------------------------------------------------------------------------------
2. PROJECT OVERVIEW
--------------------------------------------------------------------------------
This project is a real-time, desktop-style operating system mockup built using
C++17, Dear ImGui (v1.91), GLFW (v3.4), and OpenGL 3.3. It demonstrates an
immediate-mode window compositor managing desktop rendering, application windows,
a taskbar with clickable icon buttons, a Windows-style Task Manager, and clean
application shutdown handling.

--------------------------------------------------------------------------------
3. PREREQUISITES & ENVIRONMENT
--------------------------------------------------------------------------------
- Windows 10 / 11
- C++ Compiler with C++17 support (MinGW-w64 GCC recommended: C:\mingw64\bin)
- CMake 3.16 or higher
- Ninja or MinGW Makefiles build tool
- Dependencies (GLFW, Dear ImGui) are automatically downloaded and compiled
  via CMake's FetchContent on the first build. No manual library installs required.

--------------------------------------------------------------------------------
4. HOW TO RUN THE PROGRAM
--------------------------------------------------------------------------------

METHOD A: Running via VS Code
1. Open the project folder (OS_EMULATOR) in Visual Studio Code.
2. Ensure the "C/C++" extension is installed.
3. Press "F5" (or "Ctrl + F5") or go to the Run & Debug tab and click
   "Run CSOPESY OS".
4. The project will automatically compile via CMake and launch the GUI window.

METHOD B: Running via Terminal / PowerShell
1. Open PowerShell in the root project directory (OS_EMULATOR).
2. Ensure your MinGW-w64 compiler is in your PATH:
     $env:PATH = "C:\mingw64\bin;" + $env:PATH
3. Configure and build the project using CMake:
     cmake -B build -G "Ninja" -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe"
     cmake --build build
4. Launch the executable:
     .\build\src\apps\CSOPESY_OS.exe

METHOD C: Running Directly from Windows Explorer
1. Navigate to: OS_EMULATOR\build\src\apps\
2. Double-click "CSOPESY_OS.exe".

--------------------------------------------------------------------------------
5. RUNTIME CONFIGURATION (NO RECOMPILATION NEEDED)
--------------------------------------------------------------------------------
To satisfy black-box testing parameter modifications without recompiling the
code, configuration settings can be adjusted in:
   config/config.ini

Available parameters:
- window_width   : Window width in pixels (e.g., 1280)
- window_height  : Window height in pixels (e.g., 720)
- taskbar_height : Taskbar height in pixels (e.g., 48)
- clock_format   : strftime date/time format (e.g., %A, %b %d, %Y | %I:%M %p)

--------------------------------------------------------------------------------
6. APPLICATION CONTROLS & FEATURES
--------------------------------------------------------------------------------
- Boot Screen    : Animated ASCII logo and loading screen on startup.
- Desktop        : Fullscreen wallpaper (assets/wallpaper.png) with live clock.
- File Explorer  : Taskbar button opens multi-pane directory browser.
- System Info    : Taskbar button opens system specs and live uptime counter.
- Task Manager   : Taskbar button opens Windows-style processes table with
                   live CPU % and Memory (MB) utilization indicators.
- Shutdown (PWR) : Red button on the right edge of the taskbar triggers an
                   animated shutdown screen and exits the application cleanly.

================================================================================
