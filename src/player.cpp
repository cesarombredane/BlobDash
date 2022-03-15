#include "../include/player.h"

#include "iostream"
#include "cmath"

using namespace std;

Player::Player(Input *input, Map *map) {
    if (!this->texture.loadFromFile("../assets/graphics/player.png"))
        cerr << "error : player image not found" << endl;

    this->collision_up = this->collision_down = this->collision_left = this->collision_right =
            collision_up_left = collision_up_right = collision_down_left = collision_down_right = -1;
    this->grounded = false;
    this->wall_left = false;
    this->wall_right = false;
    this->d_jump = false;
    this->dash = false;
    this->counter_frame_jump = 0;
    this->counter_frame_dash = 0;
    this->counter_frame_wall_jump = 0;
    this->wall_jump_dir = 0;
    this->input = input;
    this->map = map;
    this->state = s_stand;
}

void Player::collision() {
    this->collision_up = this->collision_down = this->collision_left = this->collision_right =
        collision_up_left = collision_up_right = collision_down_left = collision_down_right = -1;

    // up
    if (this->speed.y < 0) {
        if (this->position.y + this->speed.y < 0)
            this->collision_up = this->position.y;
        else if (this->map->get_map_value(floor((this->position.x) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0 ||
                 this->map->get_map_value(floor((this->position.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0)
            this->collision_up = this->position.y % Map::TILE_SIZE;
    }

    // down
    if (this->speed.y > 0) {
        if (this->position.y + this->speed.y + Map::TILE_SIZE > this->map->get_height() * Map::TILE_SIZE)
            this->collision_down = this->map->get_height() * Map::TILE_SIZE - (this->position.y + Map::TILE_SIZE);
        else if (this->map->get_map_value(floor(this->position.x / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0 ||
                 this->map->get_map_value(floor((this->position.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
            this->collision_down = this->position.y % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.y % Map::TILE_SIZE);
    }

    // left
    if (this->speed.x < 0) {
        if (this->position.x + this->speed.x < 0)
            this->collision_left = this->position.x;
        else if (this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor(this->position.y / Map::TILE_SIZE)) > 0 ||
                 this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor((this->position.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
            this->collision_left = this->position.x % Map::TILE_SIZE;
    }

    // right
    if (this->speed.x > 0) {
        if (this->position.x + this->speed.x + Map::TILE_SIZE > this->map->get_width() * Map::TILE_SIZE)
            this->collision_right = this->map->get_width() * Map::TILE_SIZE - (this->position.x + Map::TILE_SIZE);
        else if (this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor(this->position.y / Map::TILE_SIZE)) > 0 ||
                 this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
            this->collision_right = this->position.x % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.x % Map::TILE_SIZE);
    }

    // up_left
    if (this->speed.y < 0 && this->speed.x < 0) {
        if (this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0)
            this->collision_up_left = this->position.x % Map::TILE_SIZE;
    }

    // up_right
    if (this->speed.y < 0 && this->speed.x > 0) {
        if (this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0)
            this->collision_up_right = this->position.x % Map::TILE_SIZE;
    }

    // down_left
    if (this->speed.y > 0 && this->speed.x < 0) {
        if (this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
            this->collision_down_left = this->position.x % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.x % Map::TILE_SIZE);
    }

    // down_right
    if (this->speed.y > 0 && this->speed.x > 0) {
        if (this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
            this->collision_down_right = this->position.x % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.x % Map::TILE_SIZE);
    }
}

void Player::move() {
    // acceleration
    this->acceleration.x = this->input->get_x() * this->ACCELERATION;
    this->state = this->acceleration.x == 0 ? s_stand : s_walk;

    // gravity
    this->acceleration.y = this->GRAVITY;

    // jump
    if ((this->input->get_jump() && this->grounded) || this->counter_frame_jump != 0) {
        this->state = this->d_jump ? s_jump : s_djump;
        this->acceleration.y = -this->JUMP_ACCELERATION;
        this->counter_frame_jump = ++this->counter_frame_jump % this->NB_FRAME_JUMP;
        this->input->set_jump(false);
    }
    // wall-jump
    else if (this->input->get_jump() && (this->wall_left || this->wall_right)) {
        this->counter_frame_jump = 1;
        this->counter_frame_wall_jump = 1;
        this->wall_jump_dir = this->wall_left ? 1 : -1;
        this->speed.y = 0;
    }
    // d-jump
    else if (this->input->get_jump() && this->d_jump && !this->grounded) {
        this->counter_frame_jump = 1;
        this->d_jump = false;
        this->speed.y = 0;
    }

    // wall jump x
    if (this->counter_frame_wall_jump != 0) {
        this->acceleration.x = this->wall_jump_dir * this->JUMP_ACCELERATION;
        this->counter_frame_wall_jump = ++this->counter_frame_wall_jump % this->NB_FRAME_JUMP;
    }

    // speed
    if (this->acceleration.y > 0) this->speed.y = min(this->speed.y + this->acceleration.y, this->MAX_SPEED_GRAVITY);
    else if (this->acceleration.y < 0) this->speed.y = max(this->speed.y + this->acceleration.y, -this->MAX_SPEED_JUMP);
    else this->speed.y = 0;

    if (this->acceleration.x > 0) this->speed.x = min(this->speed.x + this->acceleration.x, this->MAX_SPEED);
    else if (this->acceleration.x < 0) this->speed.x = max(this->speed.x + this->acceleration.x, -this->MAX_SPEED);
    else this->speed.x = 0;

    // dash
    if (this->input->get_dash() && this->dash || this->counter_frame_dash != 0) {
        this->state = s_dash;
        this->speed.x *= 3;
        if (this->speed.x != 0)
            this->speed.y = 0;
        this->counter_frame_dash = ++this->counter_frame_dash % this->NB_FRAME_DASH;
        this->dash = false;
    }

    // collision
    this->collision();

    // position
    this->grounded = false;
    if (this->collision_up != -1)
        this->position.y -= this->collision_up;
    else if (this->collision_down != -1) {
        this->position.y += this->collision_down;
        this->d_jump = true;
        this->dash = true;
        this->grounded = true;
    }
    else {
        if ((this->collision_left != -1 || this->collision_right != -1) && this->speed.y > 0) {
            this->state = s_wall;
            this->speed.y /= 2;
        }
        else if (this->speed.y > 0) this->state = s_fall;
        this->position.y += this->speed.y;
    }

    if (this->collision_left != -1 || (this->collision_up_left != -1 && this->collision_up == -1) || (this->collision_down_left != -1 && this->collision_down == -1)) {
        this->position.x -= this->collision_left;
        this->wall_left = true;
        this->wall_right = false;
    }
    else if (this->collision_right != -1 || (this->collision_up_right != -1 && this->collision_up == -1) || (this->collision_down_right != -1 && this->collision_down == -1)) {
        this->position.x += this->collision_right;
        this->wall_right = true;
        this->wall_left = false;
    }
    else {
        this->position.x += this->speed.x;
        if (this->speed.x != 0) this->wall_left = this->wall_right = false;
    }
}

void Player::draw_player(RenderWindow &window) {
    Sprite player;
    player.setTexture(this->texture);
    player.setPosition((Vector2f) this->position);
    window.draw(player);
}

void Player::show_collision() const {
    if (this->collision_up != -1) cout << "up = " << this->collision_up << endl;
    if (this->collision_down != -1) cout << "down = " << this->collision_down << endl;
    if (this->collision_left != -1) cout << "left = " << this->collision_left << endl;
    if (this->collision_right != -1) cout << "right = " << this->collision_right << endl;

}

void Player::show_state() const {
    cout << "State: " << this->state << endl;
}

void Player::show_position() const {
    cout << "position : " << endl;
    cout << "x = " << this->position.x << " | y = " << this->position.y << endl;
}

void Player::show_speed() const {
    cout << "x : " << this->speed.x << endl;
    cout << "y : " << this->speed.y << endl;
}