//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_MAP_H
#define RAYCASTER_MAP_H

struct Map{
    int width, height;

    Map();
    int get(int i, int j) const;
    bool isEmpty(int i, int j) const;
};

#endif //RAYCASTER_MAP_H
