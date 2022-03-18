//
// Created by tiger on 16/03/2022.
//

#include "Sprite.h"

bool Sprite::operator<(const Sprite &s) const {
    return playerDist > s.playerDist;
}
