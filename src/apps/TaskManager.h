#pragma once
#include "IApp.h"
#include <cstdio>
#include <vector>

class TaskManagerApp : public IApp {
public:
    TaskManagerApp() : IApp("Task Manager", "taskmgr.png") {
        defaultPos = ImVec2(180, 110);
        defaultSize = ImVec2(560, 380);
    }

protected:
    void drawContents() override {
        float totalCpu = 0.0f;
        int totalMem = 0;
        for (const auto& p : procs) { totalCpu += p.cpu; totalMem += p.memMB; }

        char cpuLabel[32], memLabel[32];
        std::snprintf(cpuLabel, sizeof(cpuLabel), "CPU %.1f%%", totalCpu);
        std::snprintf(memLabel, sizeof(memLabel), "Memory %d MB", totalMem);
        ImGui::ProgressBar(totalCpu / 100.0f, ImVec2(-1, 0), cpuLabel);
        ImGui::ProgressBar(totalMem / 4096.0f, ImVec2(-1, 0), memLabel);
        ImGui::Spacing();
        ImGui::Text("Processes (%d)", (int)procs.size());

        ImGuiTableFlags tf = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                             ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable;
        if (ImGui::BeginTable("processes", 4, tf)) {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("PID");
            ImGui::TableSetupColumn("CPU %");
            ImGui::TableSetupColumn("Memory (MB)");
            ImGui::TableHeadersRow();
            for (const auto& p : procs) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::TextUnformatted(p.name);
                ImGui::TableNextColumn(); ImGui::Text("%d", p.pid);
                ImGui::TableNextColumn(); ImGui::Text("%.1f", p.cpu);
                ImGui::TableNextColumn(); ImGui::Text("%d", p.memMB);
            }
            ImGui::EndTable();
        }
    }

private:
    struct Proc { const char* name; int pid; float cpu; int memMB; };
    std::vector<Proc> procs = {
        {"System", 4, 2.1f, 120},         {"explorer.exe", 1204, 1.8f, 180},
        {"csopesy_shell", 2210, 5.4f, 64}, {"chrome.exe", 3380, 14.2f, 820},
        {"code.exe", 4120, 9.7f, 450},     {"Teams.exe", 5012, 3.3f, 300},
        {"svchost.exe", 876, 0.8f, 35},    {"Discord.exe", 6044, 4.0f, 210},
    };
};
