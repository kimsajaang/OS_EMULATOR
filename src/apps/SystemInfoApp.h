#pragma once
#include "IApp.h"

class SystemInfoApp : public IApp {
public:
    SystemInfoApp() : IApp("System Info", "sysinfo.png") { defaultPos = ImVec2(140, 90); }

protected:
    void drawContents() override {
        ImGui::TextColored(ImVec4(0.35f, 1.0f, 0.75f, 1.0f), "CSOPESY Operating System Emulator v1.0");
        ImGui::Separator();
        ImGui::Text("CPU:     I7 14TH GEN");
        ImGui::Text("RAM:      69 MB");
        ImGui::Text("Display:  GLFW + OpenGL + Dear ImGui");
        ImGui::Text("Uptime:   %.0f s", ImGui::GetTime());
        ImGui::Spacing();
        ImGui::TextDisabled("Placeholder information screen.");
    }
};
