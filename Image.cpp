//
// Created by tiger on 16/03/2022.
//

#include <cassert>
#include "Image.h"

void Image::setPixel(int x, int y, uint32_t color) {
//    assert(image.size() == width * height && x < width && y < height);
    if(x >= width || y >= height)
        return;
    image[x + y * width] = color;
}

void Image::drawRectangle(int x, int y, int rectangleWidth, int rectangleHeight, uint32_t color) {
    assert(image.size() == width * height);
    for (int i = 0; i < rectangleWidth; ++i) {
        for (int j = 0; j < rectangleHeight; ++j) {
            int currentX = x + i;
            int currentY = y + j;
            if (currentX < width && currentY < height) {
                setPixel(currentX, currentY, color);
            }
        }
    }
}

void Image::fill(uint32_t color) {
    image = std::vector<uint32_t>(width * height, color);
}
