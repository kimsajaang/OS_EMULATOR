#pragma once
#include <GLFW/glfw3.h>
#include <string>

struct Texture {
    GLuint id = 0;
    int width = 0;
    int height = 0;
    bool isValid() const { return id != 0; }
};

Texture loadTexture(const std::string& filename);
