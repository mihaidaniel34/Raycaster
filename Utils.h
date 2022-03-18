//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_UTILS_H
#define RAYCASTER_UTILS_H

#include <cstdint>
#include <string>
#include <vector>

uint32_t packColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255);
void unpackColor(const uint32_t &color, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha);
void dropPpmImage(const std::string& fileName, const std::vector<uint32_t> &image, int width, int height);
#endif //RAYCASTER_UTILS_H
