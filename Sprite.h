//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_SPRITE_H
#define RAYCASTER_SPRITE_H

struct Sprite{
    float x,y;
    int textureId;
    float playerDist;
    bool operator <(const Sprite&s) const;
};

#endif //RAYCASTER_SPRITE_H
