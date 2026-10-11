#pragma once
#include "imgui.h"
#include <string>
#include <utility>

// Base class for every window the "OS" can open.
class IApp {
public:
    explicit IApp(std::string windowTitle) : title(std::move(windowTitle)) {}
    virtual ~IApp() = default;

    void render() {
        if (!isOpen) return;
        ImGui::SetNextWindowPos(defaultPos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(defaultSize, ImGuiCond_FirstUseEver);
        if (ImGui::Begin(title.c_str(), &isOpen)) drawContents();
        ImGui::End();
    }
    void toggle() { isOpen = !isOpen; }

    bool isOpen = false;
    std::string title;

protected:
    virtual void drawContents() = 0;
    ImVec2 defaultPos{120, 80};
    ImVec2 defaultSize{520, 360};
};
