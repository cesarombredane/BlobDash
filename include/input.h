#ifndef BLOB_DASH_INPUT_H
#define BLOB_DASH_INPUT_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Input {
private:
    bool up, down, left, right;

public:
    Input();

    bool get_up() const;
    bool get_down() const;
    bool get_left() const;
    bool get_right() const;

    void input(RenderWindow &window, Event &event);
    void show_input() const;
};

#endif
