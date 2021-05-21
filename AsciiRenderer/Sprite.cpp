#include "Sprite.h"
#include <math.h>

bool Sprite::set_texture(char* filePath) {
    std::ifstream f;
    f.open(filePath, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        return false;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        f.close();
        return false;
    }

    unsigned char informationheader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationheader), informationHeaderSize);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    int width = informationheader[4] + (informationheader[5] << 8) + (informationheader[6] << 16) + (informationheader[7] << 24);
    int height = informationheader[8] + (informationheader[9] << 8) + (informationheader[10] << 16) + (informationheader[11] << 24);
    m_width = width;
    m_height = height;

    if (texture != NULL) {
        delete[] texture;
        texture = NULL;
    }
    texture = new color[width * height];
    const int paddingAmount = ((4 - (width * 3) % 4) % 4);

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            int_fast8_t color[3];
            f.read(reinterpret_cast<char*>(color), 3);
            texture[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            texture[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            texture[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }

    f.close();

    return true;
}
color* Sprite::get_texture() const {
    return texture;
}
unsigned int Sprite::width()const {
    return m_width;
}
unsigned int Sprite::height()const {
    return m_height;
}
void Sprite::flush_texture() {
    delete[] texture;
    texture = NULL;
}