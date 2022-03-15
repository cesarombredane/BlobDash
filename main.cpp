#include "SFML/Graphics.hpp"
#include "include/map.h"
#include "include/input.h"
#include "include/player.h"

using namespace sf;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BlobDash");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    auto *map = new Map();
    map->load_map("1");

    Event event{};
    auto *input = new Input();

    auto player = new Player(input, map);

    while (window.isOpen()) {
        input->input(window, event);

        player->move();
        player->show_state();

        window.clear();

        map->draw_map(window);
        player->draw_player(window);

        window.display();
    }

    return 0;
}

// TODO : create player frame :
/*
 * stand : loop
 * walk : loop
 * jump : 12 frames
 * d_jump : 12 frames
 * wall : x frames + const
 * dash : 6 frames
 * fall : x frames + const
 */

// TODO : draw player good frames
