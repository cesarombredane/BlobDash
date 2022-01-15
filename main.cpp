#include "SFML/Graphics.hpp"
#include "include/map.h"
#include "include/input.h"

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

    while (window.isOpen()) {
        input->input(window, event);
        input->show_input();

        window.clear();

        map->draw_map(window);

        window.display();
    }

    return 0;
}