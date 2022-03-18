//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_TEXTURE_H
#define RAYCASTER_TEXTURE_H
#include <vector>
#include <cstdint>
#include <string>

struct Texture{
    int imageWidth, imageHeight;
    int count, size;
    std::vector<uint32_t> textures;
    

    explicit Texture(const std::string& fileName, uint32_t format);
    uint32_t &get(int i, int j, int textureIndex);
    std::vector<uint32_t> getScaledColumn(int textureId, int textureCoord, int columnHeight);

    void getTexture(const std::string &fileName) ;

    void loadColors(const unsigned char *pixmap);
};
#endif //RAYCASTER_TEXTURE_H
