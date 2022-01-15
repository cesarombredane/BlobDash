#ifndef BLOB_DASH_INPUT_H
#define BLOB_DASH_INPUT_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Input {
private:
    bool left, right;

public:
    Input();

    void input(RenderWindow &window, Event &event);
    void show_input();
};

#endif
