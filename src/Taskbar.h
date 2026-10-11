#pragma once
#include "imgui.h"
#include "apps/IApp.h"
#include <memory>
#include <string>
#include <vector>

// Fixed panel at the bottom: app icon buttons and a shutdown button.
class Taskbar {
public:
    explicit Taskbar(float h) : height(h) {}
    float height;

    // Returns true when PWR was clicked.
    bool render(std::vector<std::unique_ptr<IApp>>& apps) {
        ImVec2 display = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowPos(ImVec2(0, display.y - height));
        ImGui::SetNextWindowSize(ImVec2(display.x, height));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.10f, 0.15f, 0.96f));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoScrollWithMouse;
        bool pwr = false;
        const float btnHeight = height - 12.0f;
        const float btnWidth = 145.0f;

        ImGui::Begin("##taskbar", nullptr, flags);

        ImDrawList* dl = ImGui::GetWindowDrawList();

        for (size_t i = 0; i < apps.size(); ++i) {
            auto& app = apps[i];
            bool open = app->isOpen;

            ImGui::PushID(static_cast<int>(i));
            if (open) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.35f, 0.60f, 0.90f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.26f, 0.45f, 0.75f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.15f, 0.22f, 0.70f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.20f, 0.25f, 0.35f, 0.85f));
            }

            ImVec2 p0 = ImGui::GetCursorScreenPos();
            if (ImGui::Button(("##btn_" + std::to_string(i)).c_str(), ImVec2(btnWidth, btnHeight))) {
                app->toggle();
            }
            ImVec2 p1 = ImGui::GetItemRectMax();

            // Active underline indicator
            if (open) {
                dl->AddRectFilled(ImVec2(p0.x + 4.0f, p1.y - 2.5f),
                                  ImVec2(p1.x - 4.0f, p1.y),
                                  IM_COL32(50, 160, 255, 255), 1.0f);
            }

            // Draw Icon if valid
            float iconSize = btnHeight - 10.0f;
            float iconX = p0.x + 8.0f;
            float iconY = p0.y + (btnHeight - iconSize) * 0.5f;
            if (app->icon.isValid()) {
                dl->AddImage((ImTextureID)(intptr_t)app->icon.id,
                             ImVec2(iconX, iconY),
                             ImVec2(iconX + iconSize, iconY + iconSize));
            }

            // Draw Title next to icon
            float textX = iconX + iconSize + 8.0f;
            float textY = p0.y + (btnHeight - ImGui::GetFontSize()) * 0.5f;
            dl->AddText(ImVec2(textX, textY), IM_COL32(235, 240, 245, 255), app->title.c_str());

            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("%s", app->title.c_str());
            }

            ImGui::PopStyleColor(2);
            ImGui::PopID();
            ImGui::SameLine();
        }

        const float w = 70.0f;
        ImGui::SetCursorPosX(display.x - 12.0f - w);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.72f, 0.14f, 0.14f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.90f, 0.22f, 0.22f, 1.0f));
        if (ImGui::Button("PWR", ImVec2(w, btnHeight))) pwr = true;
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Shutdown CSOPESY OS");
        }
        ImGui::PopStyleColor(2);

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
        return pwr;
    }
};
