//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_IMAGE_H
#define RAYCASTER_IMAGE_H

#include <cstdint>
#include <vector>

struct Image {
    int width, height;
    std::vector<uint32_t> image;

    /// Set pixel to given color
    /// \param x - the x coordinate
    /// \param y - the y coordinate
    /// \param color - packed rgb value
    void setPixel(int x, int y, uint32_t color);

    /// Draw a rectangle of given size and color
    /// \param x - the x coordinate of the top left corner
    /// \param y - the y coordinate of the top left corner
    /// \param rectangleWidth - the width of the rectangle to be drawn
    /// \param rectangleHeight - the height of the rectangle to be drawn
    /// \param color
    void drawRectangle(int x, int y, int rectangleWidth, int rectangleHeight, uint32_t color);

    /// Fill the screen with the given color
    /// \param color
    void fill(uint32_t color);
};


#endif //RAYCASTER_IMAGE_H
