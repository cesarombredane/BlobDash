#ifndef BLOB_DASH_PLAYER_H
#define BLOB_DASH_PLAYER_H

#include "SFML/Graphics.hpp"
#include "input.h"
#include "map.h"

using namespace sf;

class Player {
private:
    const int MAX_SPEED = 15;
    const int ACCELERATION = 4;

    Texture texture;
    Input *input;
    Map *map;

    Vector2i position, speed, acceleration;
    int collision_up, collision_down, collision_left, collision_right,
        collision_up_left, collision_up_right, collision_down_left, collision_down_right;

public:
    Player(Input*, Map*);

    void collision();
    void move();
    void draw_player(RenderWindow &window);

    void show_collision() const;
    void show_position() const;
};

#endif
