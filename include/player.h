#ifndef BLOB_DASH_PLAYER_H
#define BLOB_DASH_PLAYER_H

#include "SFML/Graphics.hpp"
#include "input.h"
#include "map.h"

using namespace sf;

class Player {
private:
    Texture texture;
    Input *input;
    Map *map;

    Vector2i position, speed;

    int collision_up, collision_down, collision_left, collision_right;

public:
    Player(Input*, Map*);

    void collision();
    void move();
    void draw_player(RenderWindow &window);

    void show_collision() const;
    void show_position() const;
};

#endif
