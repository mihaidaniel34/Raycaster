#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>

#include "Texture.h"
#include "Image.h"
#include "Map.h"
#include "Player.h"
#include "Utils.h"
#include "Sprite.h"
#include "Renderer.h"
#include "SDL.h"


int main(int argv, char **args) {
    Image image{1024, 512, std::vector<uint32_t>(1024 * 512, packColor(255, 255, 255, 255))};
    Player player{3.45, 2.34, 1.52, M_PI / 3.};
    Map map;
    Texture texture("../walltext.bmp", SDL_PIXELFORMAT_ABGR8888);
    Texture monsters("../monsters.bmp", SDL_PIXELFORMAT_ABGR8888);
    if (!texture.count || !monsters.count) {
        std::cerr << "Failed to load textures" << std::endl;
        return -1;
    }
    std::vector<Sprite> sprites{{3.523, 3.812,  2, 0},
                                {1.834, 8.765,  0, 0},
                                {5.323, 5.365,  1, 0},
                                {4.123, 10.265, 1, 0}};
    render(image, map, player, sprites, texture, monsters);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    }

    if (SDL_CreateWindowAndRenderer(image.width, image.height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window,
                                    &renderer)) {
        std::cerr << "Couldn't create window and renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Texture *imageTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
                                                  image.width, image.height);
    SDL_UpdateTexture(imageTexture, NULL, reinterpret_cast<void *> (image.image.data()), image.width * 4);

    auto time1 = std::chrono::high_resolution_clock::now();
    while (true) {
        {
            auto time2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> timeDelta = time2 - time1;
            if (timeDelta.count() < 20) {
                std::this_thread::sleep_for(std::chrono::milliseconds(3));
                continue;
            }
            time1 = time2;
        }
        {
            SDL_Event event;
            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    break;
                }
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == 'w')
                        player.walk = 1;
                    if (event.key.keysym.sym == 'a')
                        player.turn = -1;
                    if (event.key.keysym.sym == 's')
                        player.walk = -1;
                    if (event.key.keysym.sym == 'd')
                        player.turn = 1;
                }
                if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == 'w' || event.key.keysym.sym == 's')
                        player.walk = 0;
                    if (event.key.keysym.sym == 'a' || event.key.keysym.sym == 'd')
                        player.turn = 0;
                }
            }
        }
        {
            player.viewDirection +=
                    float(player.turn) * .05; // TODO measure elapsed time and modify the speed accordingly
            float newX = player.x + player.walk * cos(player.viewDirection) * .05;
            float newY = player.y + player.walk * sin(player.viewDirection) * .05;

            if (int(newX) >= 0 && int(newX) < int(map.width) && int(newY) >= 0 && int(newY) < int(map.height)) {
                if (map.isEmpty(newX, player.y)) player.x = newX;
                if (map.isEmpty(player.x, newY)) player.y = newY;
            }
            for (auto &sprite: sprites) { // update the distances from the player to each sprite
                sprite.playerDist = std::sqrt(pow(player.x - sprite.x, 2) + pow(player.y - sprite.y, 2));
            }
            std::sort(sprites.begin(), sprites.end()); // sort it from farthest to closest
        }
        render(image, map, player, sprites, texture, monsters);
        {
            SDL_UpdateTexture(imageTexture, NULL, reinterpret_cast<void *> (image.image.data()), image.width * 4);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}