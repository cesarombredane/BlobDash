#ifndef BLOB_DASH_PLAYER_H
#define BLOB_DASH_PLAYER_H

#include "SFML/Graphics.hpp"
#include "input.h"
#include "map.h"

using namespace sf;

class Player {
private:
    const int MAX_SPEED = 8;
    const int MAX_SPEED_GRAVITY = 12;
    const int ACCELERATION = 2;
    const int GRAVITY = 4;
    const int JUMP_ACCELERATION = 6;

    const int NB_FRAME_JUMP = 12;
    const int NB_FRAME_DASH = 6;
    const int NB_FRAME_WALL_JUMP = 12;

    Texture texture;
    Input *input;
    Map *map;

    Vector2i position, speed, acceleration;

    int collision_up, collision_down, collision_left, collision_right,
        collision_up_left, collision_up_right, collision_down_left, collision_down_right;

    bool grounded;
    bool wall_left;
    bool wall_right;

    bool d_jump;
    bool dash;

    int counter_frame_jump;
    int counter_frame_dash;
    int counter_frame_wall_jump;
    int wall_jump_dir;

public:
    Player(Input*, Map*);

    void collision();
    void move();
    void draw_player(RenderWindow &window);

    void show_collision() const;
    void show_position() const;
    void show_state() const;
    void show_speed() const;
};

#endif
