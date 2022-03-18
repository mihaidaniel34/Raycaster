//
// Created by tiger on 16/03/2022.
//

#include <cassert>
#include <fstream>
#include "Utils.h"

uint32_t packColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    return (alpha << 24) + (blue << 16) + (green << 8) + red;
}

void unpackColor(const uint32_t &color, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha) {
    red = (color >> 0) & 255;
    green = (color >> 8) & 255;
    blue = (color >> 16) & 255;
    alpha = (color >> 24) & 255;
}

void dropPpmImage(const std::string &fileName, const std::vector<uint32_t> &image, int width, int height) {
    assert(image.size() == width * height);
    std::ofstream ofs(fileName, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height * width; ++i) {
        uint8_t red, green, blue, alpha;
        unpackColor(image[i], red, green, blue, alpha);
        ofs << static_cast<char>(red) << static_cast<char>(green) << static_cast<char>(blue);
    }
    ofs.close();
}
