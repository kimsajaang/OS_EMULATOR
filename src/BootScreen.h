#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <chrono>
#include <cfloat>
#include <string>

namespace BootScreen {

inline void drawCentered(ImDrawList* drawList, const char* text, float y,
                         float fontSize, ImU32 color) {
    ImFont* font = ImGui::GetFont();
    ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    drawList->AddText(font, fontSize,
                      ImVec2((displaySize.x - textSize.x) * 0.5f, y), color, text);
}

inline void render(GLFWwindow* window, float durationSeconds = 3.0f) {
    const auto start = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        const float elapsed = std::chrono::duration<float>(
            std::chrono::steady_clock::now() - start).count();
        if (elapsed >= durationSeconds) break;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        const ImU32 cyan = IM_COL32(0, 126, 166, 255);
        const ImU32 white = IM_COL32(220, 220, 220, 255);
        const ImU32 green = IM_COL32(60, 210, 85, 255);

        const char* logo[] = {
            R"(   ______ _____ ____  ____  ________________  )",
            R"(  / ____// ___// __ \/ __ \/ ____/ ___/\ \/ / )",
            R"( / /     \__ \/ / / / /_/ / __/  \__ \  \  /  )",
            R"(/ /___  ___/ / /_/ / ____/ /___ ___/ /  / /   )",
            R"(\____/ /____/\____/_/   /_____//____/  /_/    )"
        };
        for (int i = 0; i < 5; ++i) {
            drawCentered(drawList, logo[i], displaySize.y * 0.13f + i * 22.0f,
                         20.0f, cyan);
        }

        drawCentered(drawList, "Welcome to CSOPESY OS Emulator!",
                     displaySize.y * 0.38f, 18.0f, green);
        drawCentered(drawList,
                     "Group developer: Fabregas, Matthew M. | Ibanez, Kane Joshua T. | Li, Bowen | Teoxon, Jat R.",
                     displaySize.y * 0.47f, 14.0f, white);

        int dotCount = static_cast<int>(elapsed * 2.0f) % 4;
        std::string loading = "Loading" + std::string(dotCount, '.');
        drawCentered(drawList, loading.c_str(), displaySize.y * 0.88f, 16.0f, green);

        ImGui::Render();
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

inline void renderShutdown(GLFWwindow* window, float durationSeconds = 1.0f) {
    const auto start = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        const float elapsed = std::chrono::duration<float>(
            std::chrono::steady_clock::now() - start).count();
        if (elapsed >= durationSeconds) break;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        float fadeIn = elapsed / 0.25f;
        float fadeOut = (durationSeconds - elapsed) / 0.25f;
        float opacity = fadeIn < 1.0f ? fadeIn : 1.0f;
        if (fadeOut < opacity) opacity = fadeOut;
        if (opacity < 0.0f) opacity = 0.0f;
        ImU32 textColor = IM_COL32(210, 220, 230,
                                   static_cast<int>(opacity * 255.0f));

        drawList->AddRectFilled(ImVec2(0.0f, 0.0f), displaySize,
                                IM_COL32(0, 0, 0, 255));
        drawCentered(drawList, "Shutting down...", displaySize.y * 0.45f,
                     22.0f, textColor);

        const float barWidth = displaySize.x * 0.28f;
        const float barHeight = 4.0f;
        const float barLeft = (displaySize.x - barWidth) * 0.5f;
        const float barTop = displaySize.y * 0.54f;
        drawList->AddRectFilled(ImVec2(barLeft, barTop),
                                ImVec2(barLeft + barWidth, barTop + barHeight),
                                IM_COL32(35, 45, 55, 255), 2.0f);
        drawList->AddRectFilled(ImVec2(barLeft, barTop),
                                ImVec2(barLeft + barWidth * (elapsed / durationSeconds),
                                       barTop + barHeight),
                                IM_COL32(80, 170, 210, 255), 2.0f);

        ImGui::Render();
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

}  // namespace BootScreen
