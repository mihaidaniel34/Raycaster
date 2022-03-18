//
// Created by tiger on 16/03/2022.
//

#ifndef RAYCASTER_PLAYER_H
#define RAYCASTER_PLAYER_H

struct Player {
    float x, y;
    float viewDirection;
    float fieldOfView;
    int turn = 0;
    int walk = 0;
};
#endif //RAYCASTER_PLAYER_H
