#pragma once
#include "imgui.h"
#include "Config.h"
#include <ctime>

// Base layer of the OS: clock and version label behind every ImGui window.
class Desktop {
public:
    void render(const Config& cfg, float taskbarHeight) {
        ImDrawList* dl = ImGui::GetBackgroundDrawList();
        ImVec2 size = ImGui::GetIO().DisplaySize;
        drawClock(dl, size, cfg);

        const char* label = "CSOPESY OS v1.0";
        dl->AddText(ImVec2(16.0f, size.y - taskbarHeight - 26.0f),
                    IM_COL32(160, 170, 180, 255), label);
    }

private:
    void drawClock(ImDrawList* dl, ImVec2 size, const Config& cfg) {
        std::time_t now = std::time(nullptr);
        std::tm tmv{};
#if defined(_MSC_VER)
        localtime_s(&tmv, &now);
#else
    if (const std::tm* local = std::localtime(&now)) tmv = *local;
#endif
        char buf[128];
        std::strftime(buf, sizeof(buf), cfg.clockFormat.c_str(), &tmv);

        ImVec2 ts = ImGui::CalcTextSize(buf);
        ImVec2 pad(10.0f, 6.0f);
        ImVec2 max(size.x - 12.0f, 12.0f + ts.y + pad.y * 2);
        ImVec2 min(max.x - ts.x - pad.x * 2, 12.0f);
        dl->AddRectFilled(min, max, IM_COL32(10, 15, 25, 200), 4.0f);
        dl->AddText(ImVec2(min.x + pad.x, min.y + pad.y),
                    IM_COL32(200, 255, 230, 255), buf);
    }
};
