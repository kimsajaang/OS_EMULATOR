# CSOPESY Semi-Major Output 2: Desktop-Style OS Mock-up
### Group 6

## 👥 Group Members
* **Fabregas, Matthew M.**
* **Ibanez, Kane Joshua T.**
* **Li, Bowen**
* **Teoxon, Jat R.**

**Course:** CSOPESY  

---

## 📌 1. Entry File & Function Location
* **Entry File:** [`src/main.cpp`](src/main.cpp)
* **Main Function:** `int main()` (Line 17)

---

## 💻 2. Project Overview
This project is a real-time, desktop-style operating system mockup built using **C++17**, **Dear ImGui (v1.91)**, **GLFW (v3.4)**, and **OpenGL 3.3**. It demonstrates an immediate-mode compositor that manages desktop rendering, application windows, a taskbar with clickable icon buttons, a Windows-style Task Manager, and clean shutdown handling.

---

## ⚙️ 3. How to Run the Program

### Method A: Visual Studio Code (Recommended for Video Submission)
1. Open the project root folder (`OS_EMULATOR`) in VS Code.
2. Press **`F5`** (or **`Ctrl + F5`**), or click the green **Play** button under the **Run & Debug** tab (`Run CSOPESY OS`).
3. The program will automatically build and launch.

### Method B: PowerShell / Terminal
```powershell
# 1. Add MinGW to PATH (if not globally in PATH)
$env:PATH = "C:\mingw64\bin;" + $env:PATH

# 2. Configure & Build
cmake -B build -G "Ninja" -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe"
cmake --build build

# 3. Launch Executable
.\build\src\apps\CSOPESY_OS.exe
```

### Method C: Direct Executable
Navigate to `build/src/apps/` and double-click **`CSOPESY_OS.exe`**.

---

## 🛠️ 4. Runtime Configuration (No Recompilation Needed)
To satisfy black-box quiz testing under varying parameters without recompiling, configuration settings can be adjusted directly in [`config/config.ini`](config/config.ini):

```ini
window_width=1280
window_height=720
taskbar_height=48
clock_format=%A, %b %d, %Y | %I:%M %p
```

---

## 🖥️ 5. Features & Navigation
* **Boot Screen:** Animated ASCII logo, group credits, and loading indicator on startup.
* **Desktop Base Layer:** Fullscreen wallpaper (`assets/wallpaper.png`) with real-time live clock badge.
* **Taskbar:** Docked bottom panel featuring clickable icon buttons with PNG logos, active underline indicators, and hover tooltips.
* **File Explorer:** Directory navigation sidebar and file list view.
* **System Info:** Hardware/software specs and real-time uptime counter.
* **Task Manager:** Windows-style process table displaying PID, CPU %, and Memory (MB) along with utilization progress bars.
* **Clean Shutdown:** Clicking **`PWR`** triggers an animated shutdown screen and gracefully closes the program.