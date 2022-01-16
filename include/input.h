#ifndef BLOB_DASH_INPUT_H
#define BLOB_DASH_INPUT_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Input {
private:
    int x, y;

public:
    Input();

    int get_x() const;
    int get_y() const;

    void input(RenderWindow &window, Event &event);
    void show_input() const;
};

#endif
