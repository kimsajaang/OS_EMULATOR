#pragma once
#include <fstream>
#include <string>

struct Config {
    int windowWidth = 1280;
    int windowHeight = 720;
    float taskbarHeight = 48.0f;
    std::string clockFormat = "%A, %b %d, %Y | %I:%M %p";

    // Looks for config.ini relative to the working directory, then a few
    // levels up (covers running from build/ or build/Debug/).
    static Config load() {
        static const char* paths[] = {
            "config/config.ini", "../config/config.ini",
            "../../config/config.ini", "../../../config/config.ini"
        };
        Config cfg;
        for (const char* p : paths) {
            std::ifstream in(p);
            if (!in.is_open()) continue;
            std::string line;
            while (std::getline(in, line)) {
                line = trim(line);
                if (line.empty() || line[0] == '#' || line[0] == ';') continue;
                size_t eq = line.find('=');
                if (eq == std::string::npos) continue;
                cfg.apply(trim(line.substr(0, eq)), trim(line.substr(eq + 1)));
            }
            break;
        }
        return cfg;
    }

private:
    static std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    void apply(const std::string& key, const std::string& val) {
        try {
            if (key == "window_width") windowWidth = std::stoi(val);
            else if (key == "window_height") windowHeight = std::stoi(val);
            else if (key == "taskbar_height") taskbarHeight = std::stof(val);
            else if (key == "clock_format") clockFormat = val;
        } catch (...) { /* bad value: keep the default */ }
    }
};
