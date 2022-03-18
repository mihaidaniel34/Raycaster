//
// Created by tiger on 16/03/2022.
//

#include "Texture.h"
#include "Utils.h"
#include "SDL_surface.h"
#include <iostream>
#include <cassert>

Texture::Texture(const std::string &fileName, uint32_t format) : imageWidth(0), imageHeight(0), count(0), size(0) {
    SDL_Surface *temp = SDL_LoadBMP(fileName.c_str());
    if (!temp) {
        std::cerr << "Error loading texture." << SDL_GetError() << std::endl;
        return;
    }
    SDL_Surface *surface = SDL_ConvertSurfaceFormat(temp, format, 0);
    SDL_FreeSurface(temp);
    if (!surface) {
        std::cerr << "Error converting texture. " << SDL_GetError() << std::endl;
        return;
    }
    int width = surface->w;
    int height = surface->h;
    if (width * 4 != surface->pitch) {
        std::cerr << "Texture must be 32 bit." << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    if (width != height * int(width / height)) {
        std::cerr << "Texture is wrong format." << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    count = width / height;
    size = width / count;
    imageWidth = width;
    imageHeight = height;

    auto *pixmap = reinterpret_cast<uint8_t *> (surface->pixels);
    textures = std::vector<uint32_t>(width * height);
    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i) {
            uint8_t red = pixmap[(i + j * width) * 4 + 0];
            uint8_t green = pixmap[(i + j * width) * 4 + 1];
            uint8_t blue = pixmap[(i + j * width) * 4 + 2];
            uint8_t alpha = pixmap[(i + j * width) * 4 + 3];
            textures[i + j * width] = packColor(red, green, blue, alpha);
        }
    SDL_FreeSurface(surface);
}


uint32_t &Texture::get(int i, int j, int textureIndex) {
    assert(i < size && j < size && textureIndex < count);
    return textures[i + textureIndex * size + j * imageWidth];
}

std::vector<uint32_t> Texture::getScaledColumn(int textureId, int textureCoord, int columnHeight) {
    assert(textureCoord < size && textureId < count);
    std::vector<uint32_t> columns(columnHeight);
    for (int y = 0; y < columnHeight; ++y) {
        columns[y] = get(textureCoord, (y * size) / columnHeight, textureId);
    }
    return columns;
}
