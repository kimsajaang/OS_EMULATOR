#pragma once
#include "IApp.h"

class FileExplorerApp : public IApp {
public:
    FileExplorerApp() : IApp("File Explorer") { defaultPos = ImVec2(100, 70); }

protected:
    void drawContents() override {
        static const char* folders[] = {"Documents", "Downloads", "Pictures", "Music", "Videos"};
        ImGui::BeginChild("folders", ImVec2(150, 0), true);
        for (int i = 0; i < 5; i++)
            if (ImGui::Selectable(folders[i], selected == i)) selected = i;
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("This PC > %s", folders[selected]);
        ImGui::Separator();
        ImGui::BulletText("placeholder_file_1.txt");
        ImGui::BulletText("placeholder_file_2.png");
        ImGui::BulletText("placeholder_file_3.pdf");
        ImGui::EndGroup();
    }

private:
    int selected = 0;
};
