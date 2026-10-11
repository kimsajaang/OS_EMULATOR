#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <fstream>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

Texture loadTexture(const std::string& filename) {
    static const char* prefixes[] = {
        "assets/", "../assets/", "../../assets/", "../../../assets/", ""
    };

    std::string foundPath;
    for (const char* p : prefixes) {
        std::string candidate = std::string(p) + filename;
        std::ifstream f(candidate, std::ios::binary);
        if (f.is_open()) {
            foundPath = candidate;
            break;
        }
    }

    if (foundPath.empty()) {
        foundPath = filename;
    }

    int w = 0, h = 0, channels = 0;
    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(foundPath.c_str(), &w, &h, &channels, 4);
    if (!data) {
        return Texture{0, 0, 0};
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return Texture{tex, w, h};
}
