#include "../include/player.h"

#include "iostream"
#include "cmath"

using namespace std;

Player::Player(Input *input, Map *map) {
    if (!this->texture.loadFromFile("../assets/graphics/player.png"))
        cerr << "error : player image not found" << endl;

    this->position = this->speed = Vector2i(0, 0);
    this->collision_up = this->collision_down = this->collision_left = this->collision_right = -1;
    this->input = input;
    this->map = map;
}

void Player::collision() {
    // up
    if (this->position.y + this->speed.y < 0)
        this->collision_up = this->position.y;
    else if (this->map->get_map_value(floor((this->position.x) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0 ||
             this->map->get_map_value(floor((this->position.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y) / Map::TILE_SIZE)) > 0)
        this->collision_up = this->position.y % Map::TILE_SIZE;
    else this->collision_up = -1;

    // down
    if (this->position.y + this->speed.y + Map::TILE_SIZE > this->map->get_height() * Map::TILE_SIZE)
        this->collision_down = this->map->get_height() * Map::TILE_SIZE - (this->position.y + Map::TILE_SIZE);
    else if (this->map->get_map_value(floor(this->position.x / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0 ||
             this->map->get_map_value(floor((this->position.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + this->speed.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
        this->collision_down = this->position.y % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.y % Map::TILE_SIZE);
    else this->collision_down = -1;

    // left
    if (this->position.x + this->speed.x < 0)
        this->collision_left = this->position.x;
    else if (this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor(this->position.y / Map::TILE_SIZE)) > 0 ||
             this->map->get_map_value(floor((this->position.x + this->speed.x) / Map::TILE_SIZE), floor((this->position.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
        this->collision_left = this->position.x % Map::TILE_SIZE;
    else this->collision_left = -1;

    // right
    if (this->position.x + this->speed.x + Map::TILE_SIZE > this->map->get_width() * Map::TILE_SIZE)
        this->collision_right = this->map->get_width() * Map::TILE_SIZE - (this->position.x + Map::TILE_SIZE);
    else if (this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y) / Map::TILE_SIZE)) > 0 ||
             this->map->get_map_value(floor((this->position.x + this->speed.x + Map::TILE_SIZE - 1) / Map::TILE_SIZE), floor((this->position.y + Map::TILE_SIZE - 1) / Map::TILE_SIZE)) > 0)
        this->collision_right = this->position.x % Map::TILE_SIZE == 0 ? 0 : Map::TILE_SIZE - (this->position.x % Map::TILE_SIZE);
    else this->collision_right = -1;
}

void Player::move() {
    // gravité
    //this->acceleration.y = .5;
    //this->speed.y = min((float) 15, this->speed.y + this->acceleration.y);

    // mouvement
    if (this->input->get_up()) this->speed.y = -10;
    else if (this->input->get_down()) this->speed.y = 10;
    else this->speed.y = 0;

    if (this->input->get_left()) this->speed.x = -10;
    else if (this->input->get_right()) this->speed.x = 10;
    else this->speed.x = 0;

    // colision
    this->collision();

    if (this->collision_up != -1) this->position.y -= this->collision_up;
    else if (this->collision_down != -1) this->position.y += this->collision_down;
    else this->position.y += this->speed.y;

    if (this->collision_left != -1) this->position.x -= this->collision_left;
    else if (this->collision_right != -1) this->position.x += this->collision_right;
    else this->position.x += this->speed.x;
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

void Player::show_position() const {
    cout << "position : " << endl;
    cout << "x = " << this->position.x << " | y = " << this->position.y << endl;
}
