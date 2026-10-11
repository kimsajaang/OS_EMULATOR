#pragma once
#include "imgui.h"
#include "apps/IApp.h"
#include <memory>
#include <vector>

// Fixed panel at the bottom: one button per app and a shutdown button.
class Taskbar {
public:
    explicit Taskbar(float h) : height(h) {}
    float height;

    // Returns true when PWR was clicked.
    bool render(std::vector<std::unique_ptr<IApp>>& apps) {
        ImVec2 display = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowPos(ImVec2(0, display.y - height));
        ImGui::SetNextWindowSize(ImVec2(display.x, height));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.06f, 0.10f, 0.95f));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoScrollWithMouse;
        bool pwr = false;
        const ImVec2 btn(130, height - 12.0f);

        ImGui::Begin("##taskbar", nullptr, flags);

        for (auto& app : apps) {
            bool open = app->isOpen;
            if (open) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.40f, 0.75f, 1.0f));
            if (ImGui::Button(app->title.c_str(), btn)) app->toggle();
            if (open) ImGui::PopStyleColor();
            ImGui::SameLine();
        }

        const float w = 60.0f;
        ImGui::SetCursorPosX(display.x - 8.0f - w);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.65f, 0.12f, 0.12f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.85f, 0.20f, 0.20f, 1.0f));
        if (ImGui::Button("PWR", ImVec2(w, btn.y))) pwr = true;
        ImGui::PopStyleColor(2);

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
        return pwr;
    }
};
