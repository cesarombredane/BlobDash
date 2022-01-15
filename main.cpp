#include "SFML/Graphics.hpp"
#include "include/map.h"

using namespace sf;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BlobDash");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Map *map = new Map();
    map->load_map("1");

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();

        map->draw_map(window);

        window.display();
    }

    return 0;
}