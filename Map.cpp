//
// Created by tiger on 16/03/2022.
//

#include <cassert>
#include "Map.h"

static const char map[] = "0000222222220000"\
                          "1              0"\
                          "1      11111   0"\
                          "1     0        0"\
                          "0     0  1110000"\
                          "0     3        0"\
                          "0   10000      0"\
                          "0   3   11100  0"\
                          "5   4   0      0"\
                          "5   4   1  00000"\
                          "0       1      0"\
                          "2       1      0"\
                          "0       0      0"\
                          "0 0000000      0"\
                          "0              0"\
                          "0002222222200000";

Map::Map() : width(16), height(16) {
    assert(sizeof(map) == width * height + 1);
}

int Map::get(int i, int j) const {
    assert(i < width && j < height && sizeof(map) == width * height + 1);
    return map[i + j * width] - '0';
}

bool Map::isEmpty(int i, int j) const {
    assert(i < width && j < height && sizeof(map) == width * height + 1);
    return map[i + j * width] == ' ';
}
