//
// Created by tiger on 16/03/2022.
//

#include <cmath>
#include <cassert>
#include <algorithm>
#include "Renderer.h"
#include "Utils.h"


int wallXCoord(const float x, const float y, Texture &wallTexture) {
    float hitX = x - floor(x + .5);
    float hitY = y - floor(y + .5);
    int textureX = wallTexture.size;
    textureX *= std::abs(hitX) > std::abs(hitY) ? hitX : hitY;
    if (textureX < 0)
        textureX += wallTexture.size;
    assert(textureX >= 0 && textureX < wallTexture.size);
    return textureX;
}

void showSprite(Sprite &sprite, Image &image, Map &map) {
    const int rectangleWidth = image.width / (map.width * 2);
    const int rectangleHeight = image.height / map.height;
    image.drawRectangle(sprite.x * rectangleWidth - 3, sprite.y * rectangleHeight - 3, 6, 6, packColor(255, 0, 0));
}

void drawSprite(Sprite &sprite, Image &image, std::vector<float> &depthBuffer, Player &player, Texture &monster) {
    float spriteDirection = atan2(sprite.y - player.y, sprite.x - player.x);
    while (spriteDirection - player.viewDirection > M_PI) {
        spriteDirection -= 2 * M_PI;
    }
    while (spriteDirection - player.viewDirection < -M_PI) {
        spriteDirection += 2 * M_PI;
    }

//    float spriteDistance = std::sqrt(pow(player.x - sprite.x, 2) + pow(player.y - sprite.y, 2));
    int spriteSize = std::min(2000, int(image.height / sprite.playerDist));
    int horizontalOffset =
            (spriteDirection - player.viewDirection) * (image.width / 2) / (player.fieldOfView) + (image.width / 4) -
            spriteSize / 2;
    int verticalOffset = image.height / 2 - spriteSize / 2;

    for (int i = 0; i < spriteSize; ++i) {
        if (horizontalOffset + i < 0 || horizontalOffset + i > image.width / 2)
            continue;
        if (depthBuffer[horizontalOffset + i] < sprite.playerDist)
            continue;
        for (int j = 0; j < spriteSize; j++) {
            if (verticalOffset + j < 0 || verticalOffset + j > image.height)
                continue;
            uint32_t color = monster.get(i * monster.size / spriteSize, j * monster.size / spriteSize,
                                         sprite.textureId);
            uint8_t red, green, blue, alpha;
            unpackColor(color, red, green, blue, alpha);
            if (alpha > 128)
                image.setPixel(image.width / 2 + horizontalOffset + i, verticalOffset + j, color);
        }
    }

}

void render(Image &image, Map &map, Player &player, std::vector<Sprite> sprites, Texture &texture, Texture &monster) {
    image.fill(packColor(255, 255, 255));
    const int rectangleWidth = image.width / (map.width * 2);
    const int rectangleHeight = image.height / map.height;
    for (int j = 0; j < map.height; ++j) {
        for (int i = 0; i < map.width; ++i) {
            if (map.isEmpty(i, j))
                continue;
            int rectangleX = i * rectangleWidth;
            int rectangleY = j * rectangleHeight;
            int textureId = map.get(i, j);
            assert(textureId < texture.count);
            image.drawRectangle(rectangleX, rectangleY, rectangleWidth, rectangleHeight, texture.get(0, 0, textureId));
        }
    }
    std::vector<float> depthBuffer(image.width / 2, 1e3);

    for (int i = 0; i < image.width / 2; ++i) {
        float angle = player.viewDirection - player.fieldOfView / 2 + player.fieldOfView * i / float(image.width / 2);
        for (float t = 0; t < 20; t += .01) {
            float x = player.x + t * cos(angle);
            float y = player.y + t * sin(angle);
            image.setPixel(x * rectangleWidth, y * rectangleHeight, packColor(160, 160, 160));
            if (map.isEmpty(x, y))
                continue;
            int textureId = map.get(x, y);
            assert(textureId < texture.count);
            float dist = .2 + t * cos(angle - player.viewDirection);
            int columnHeight = image.height / dist;
            depthBuffer[i] = dist;
            int textureX = wallXCoord(x, y, texture);
            std::vector<uint32_t> column = texture.getScaledColumn(textureId, textureX, columnHeight);
            int pixX = i + image.width / 2;
            for (int j = 0; j < columnHeight; ++j) {
                int pixY = j + image.height / 2 - columnHeight / 2;
                if (pixY < 0 || pixY >= image.height)
                    continue;
                image.setPixel(pixX, pixY, column[j]);
            }
            break;
        }

    }
    for (auto &sprite: sprites) {
        sprite.playerDist = std::sqrt(pow(player.x - sprite.x, 2) + pow(player.y - sprite.y, 2));
    }
    std::sort(sprites.begin(), sprites.end());
    for (auto &sprite: sprites) {
        showSprite(sprite, image, map);
        drawSprite(sprite, image, depthBuffer, player, monster);
    }
}