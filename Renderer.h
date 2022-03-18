//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_RENDERER_H
#define RAYCASTER_RENDERER_H

#include "Image.h"
#include "Map.h"
#include "Player.h"
#include "Sprite.h"
#include "Texture.h"

void render(Image &image, Map &map, Player &player, std::vector <Sprite> sprites, Texture &texture, Texture &monster);

#endif //RAYCASTER_RENDERER_H
