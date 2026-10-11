#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

#include "BootScreen.h"
#include "Config.h"
#include "Desktop.h"
#include "Taskbar.h"
#include "apps/FileExplorerApp.h"
#include "apps/SystemInfoApp.h"
#include "apps/TaskManager.h"

int main() {
    Config cfg = Config::load();

    if (!glfwInit()) return 1;
    GLFWwindow* window = glfwCreateWindow(cfg.windowWidth, cfg.windowHeight,
                                          "CSOPESY Desktop OS Emulator", nullptr, nullptr);
    if (!window) { glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;  // don't persist window layout between runs
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    BootScreen::render(window);
    if (glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

    Desktop desktop;
    Taskbar taskbar(cfg.taskbarHeight);
    std::vector<std::unique_ptr<IApp>> apps;
    apps.push_back(std::make_unique<FileExplorerApp>());  // unique screen #1
    apps.push_back(std::make_unique<SystemInfoApp>());    // unique screen #2
    apps.push_back(std::make_unique<TaskManagerApp>());   // Task Manager

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED)) {
            glfwWaitEventsTimeout(0.01);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        desktop.render(cfg, taskbar.height);          // 1. wallpaper + clock
        for (auto& app : apps) app->render();         // 2. app windows
        if (taskbar.render(apps)) {                   // 3. taskbar (+ PWR)
            ImGui::Render();
            BootScreen::renderShutdown(window);
            break;
        }

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
