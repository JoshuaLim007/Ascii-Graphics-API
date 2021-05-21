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
    int size = width * height;
    texture = new color[size];
    const int paddingAmount = ((4 - (width * 3) % 4) % 4);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            //f.read((char*)(color), 3);
            int index = (size - (y * m_width + x)) - 1;
            texture[index].r = static_cast<float>(color[2]) / 255.0f;
            texture[index].g = static_cast<float>(color[1]) / 255.0f;
            texture[index].b = static_cast<float>(color[0]) / 255.0f;
            texture[index].l = get_luminance_value(texture[index].r, texture[index].g, texture[index].b);
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
float Sprite::get_luminance_value(float r, float g, float b) {
    return (0.2126f * sRGBtoLin(r) + 0.7152f * sRGBtoLin(g) + 0.0722f * sRGBtoLin(b));
}
float Sprite::sRGBtoLin(float channel) {
    if (channel <= 0.04045) {
        return channel / 12.92f;
    }
    else {
        return pow(((channel + 0.055f) / 1.055f), 2.4f);
    }
}